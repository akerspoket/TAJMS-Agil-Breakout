#include "OGLGraphicsEngine.h"



OGLGraphicsEngine::OGLGraphicsEngine()
{
}


OGLGraphicsEngine::~OGLGraphicsEngine()
{
}


int OGLGraphicsEngine::InitGlew(SDL_Window* pWND)
{
	mWindow = pWND;
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	m_glContext = SDL_GL_CreateContext(pWND);
	mObjLoader = new ObjLoader();
	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return -1;
	}
	glEnable(GL_DEPTH_TEST);
	printf("GL version: %s\n", glGetString(GL_VERSION));
	//CreateTriangle();
	Vertices = mObjLoader->LoadObj("bth.obj", vec3(0.03f, 0.03f, 0.03f));


	mVertexBufferID = CreateObjectBuffer(Vertices.data(), sizeof(Vertex)*Vertices.size(), Vertices.size());
	CompileShaders();
	InitGraphics(45.0f, 600.0f, 800.0f, 0.1f, 100, 13.0f);


	return 1;
}

void OGLGraphicsEngine::CreateTriangle()
{
	//Vertices[0] = vec3(-0.3f, -0.3f, 0.0f);
	//Vertices[1] = vec3(0.0f, 0.3f, 0.0f);
	//Vertices[2] = vec3(0.3f, -0.3f, 0.0f);
	//glGenBuffers(1, &VBO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	Vertices.push_back(Vertex(vec3(-0.3f, -0.3f, 0.0f), vec2(0.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f)));
	Vertices.push_back(Vertex(vec3(0.0f, 0.3f, 0.0f), vec2(0.5f, 0.0f), vec3(0.0f, 0.0f, 0.0f)));
	Vertices.push_back(Vertex(vec3(0.3f, -0.3f, 0.0f), vec2(1.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f)));
	
}

int OGLGraphicsEngine::CreateVertexBuffer(void* pDataStart, int pBufferSize)
{
	GLuint tTempBuffer;
	glGenBuffers(1, &tTempBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, tTempBuffer);
	glBufferData(GL_ARRAY_BUFFER, pBufferSize, pDataStart, GL_STATIC_DRAW);
	mBuffers.push_back(tTempBuffer);
	return mBuffers.size()-1;

}

int OGLGraphicsEngine::CreateObjectBuffer(void* pDataStart, int pDataSize,int pNumberOfIndices)
{
	GLuint tTempBuffer;
	glGenBuffers(1, &tTempBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, tTempBuffer);
	glBufferData(GL_ARRAY_BUFFER, pDataSize, pDataStart, GL_STATIC_DRAW);
	ObjectBufferType tBT;
	tBT.BufferHandle = tTempBuffer;
	tBT.NumberOfIndices = pNumberOfIndices;
	mObjectBuffers.push_back(tBT);
	return mObjectBuffers.size() - 1;
}

int OGLGraphicsEngine::AddUniform(GLuint pShader, const GLchar* pName)
{
	glUseProgram(pShader);
	GLuint tTempUniformLocation = glGetUniformLocation(pShader, pName);
	assert(tTempUniformLocation != 0xFFFFFFFF);
	mUniforms.push_back(tTempUniformLocation);
	return mUniforms.size() - 1;

}

void OGLGraphicsEngine::RenderFrame()
{
	SDL_GL_SwapWindow(mWindow);

	glClearColor(1.0f, 1.0f, 0.0f, 0.0f);

	static float Scale = 0.0f;
	Scale += 0.001f;


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);
	//glEnableVertexAttribArray(2);
	//glBindBuffer(GL_ARRAY_BUFFER, mBuffers[mVertexBufferID]);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(5 * sizeof(float)));
	//glDrawArrays(GL_TRIANGLES, 0, Vertices.size());
	//glDisableVertexAttribArray(0);
	//glDisableVertexAttribArray(1);
	//glDisableVertexAttribArray(2);

	mInstanceMatricesTemp.clear();
	for (size_t i = 0; i < 4; i++)
	{
		InstanceBufferType tTransMat;
		tTransMat.TranslationMatrices = glm::translate(glm::vec3((float)i*4.0f*sin(Scale), 1.0f, 1.0f));
		mInstanceMatricesTemp.push_back(tTransMat);

	}
	

	DrawObjects(mVertexBufferID, mInstanceMatricesTemp, 0);

}

void OGLGraphicsEngine::DrawObjects(int pMeshType, vector<InstanceBufferType> pInstanceBufferData, int pTextureBuffer)
{

	glBindBuffer(GL_ARRAY_BUFFER, mBuffers[mTransBuffer]);
	glBufferData(GL_ARRAY_BUFFER, pInstanceBufferData.size()* sizeof(InstanceBufferType), pInstanceBufferData.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, mObjectBuffers[pMeshType].BufferHandle);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(5 * sizeof(float)));
	glBindBuffer(GL_ARRAY_BUFFER, mBuffers[mTransBuffer]);
	for (size_t i = 0; i < 4; i++)
	{
		glEnableVertexAttribArray(3 + i);
		glVertexAttribPointer(3+i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)*i));
		glVertexAttribDivisor(3 + i, 1);
	}	
	glDrawArraysInstanced(GL_TRIANGLES, 0, mObjectBuffers[pMeshType].NumberOfIndices, pInstanceBufferData.size());
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
	glDisableVertexAttribArray(5);
	glDisableVertexAttribArray(6);

}



void OGLGraphicsEngine::InitGraphics(float pFoVAngleY, float pHeight, float pWidth, float pNear, float pFar, float pZPos)
{
	mWVPBuffer.world = glm::mat4();
	mWVPBuffer.view = glm::lookAt(glm::vec3(0.0f, 0.0f, pZPos), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0, 1, 0));
	mWVPBuffer.projection = glm::perspective(pFoVAngleY, pWidth / pHeight, pNear, pFar);

	mWVPBufferID = AddUniform(mNormalShaderProg, "gWorld");
	glUniformMatrix4fv(mUniforms[mWVPBufferID], 1, GL_FALSE, (float*)&mWVPBuffer.world);
	mWVPBufferID = AddUniform(mNormalShaderProg, "gView");
	glUniformMatrix4fv(mUniforms[mWVPBufferID], 1, GL_FALSE, (float*)&mWVPBuffer.view);
	mWVPBufferID = AddUniform(mNormalShaderProg, "gProj");
	glUniformMatrix4fv(mUniforms[mWVPBufferID], 1, GL_FALSE, (float*)&mWVPBuffer.projection);
	
	//För instanceDraw
	mTransBuffer = CreateVertexBuffer(nullptr, 0);


}


void OGLGraphicsEngine::AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
	GLuint ShaderObj = glCreateShader(ShaderType);

	if (ShaderObj == 0) {
		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
		int hi;
		std::cin >> hi;
	}

	const GLchar* p[1];
	p[0] = pShaderText;
	GLint Lengths[1];
	Lengths[0] = strlen(pShaderText);
	glShaderSource(ShaderObj, 1, p, Lengths);
	glCompileShader(ShaderObj);
	GLint success;
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];
		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
		int hi;
		std::cin >> hi;
	}

	glAttachShader(ShaderProgram, ShaderObj);
}

void OGLGraphicsEngine::CompileShaders()
{
	mNormalShaderProg = glCreateProgram();

	if (mNormalShaderProg == 0) {
		fprintf(stderr, "Error creating shader program\n");
		int hi;
		std::cin >> hi;
	}

	std::string vs, fs;

	if (!ReadFile(pVSFileName, vs)) {
		exit(1);
	};

	if (!ReadFile(pFSFileName, fs)) {
		exit(1);
	};

	AddShader(mNormalShaderProg, vs.c_str(), GL_VERTEX_SHADER);
	AddShader(mNormalShaderProg, fs.c_str(), GL_FRAGMENT_SHADER);

	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };

	glLinkProgram(mNormalShaderProg);
	glGetProgramiv(mNormalShaderProg, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(mNormalShaderProg, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
		int hi;
		std::cin >> hi;
	}

	glValidateProgram(mNormalShaderProg);
	glGetProgramiv(mNormalShaderProg, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(mNormalShaderProg, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
		int hi;
		std::cin >> hi;
	}

	glUseProgram(mNormalShaderProg);
}

bool OGLGraphicsEngine::ReadFile(const char* pFileName, string& outFile)
{
	ifstream f(pFileName);

	bool ret = false;

	if (f.is_open()) {
		string line;
		while (getline(f, line)) {
			outFile.append(line);
			outFile.append("\n");
		}

		f.close();

		ret = true;
	}
	else {
		cout << "Fel i shaderladdningen";
	}

	return ret;
}

