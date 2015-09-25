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
	//printf("GL version: %s\n", glGetString(GL_VERSION));
	//CreateTriangle();
	//Vertices = mObjLoader->LoadObj("bth.obj", 0.03f);


	mVertexBufferID = CreateVertexBuffer(Vertices.data(), sizeof(Vertex)*Vertices.size());
	CompileShaders();
	mUniformID = AddUniform(normalShaderProg, "gScale");

	glm::mat4x4 tWorldMat;




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

	glUniform1f(mUniforms[mUniformID], sinf(Scale));

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, mBuffers[mVertexBufferID]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(5 * sizeof(float)));
	glDrawArrays(GL_TRIANGLES, 0, Vertices.size());
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

}



void OGLGraphicsEngine::AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
	GLuint ShaderObj = glCreateShader(ShaderType);

	if (ShaderObj == 0) {
		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
		exit(0);
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
		exit(1);
	}

	glAttachShader(ShaderProgram, ShaderObj);
}

void OGLGraphicsEngine::CompileShaders()
{
	normalShaderProg = glCreateProgram();

	if (normalShaderProg == 0) {
		fprintf(stderr, "Error creating shader program\n");
		exit(1);
	}

	std::string vs, fs;

	if (!ReadFile(pVSFileName, vs)) {
		exit(1);
	};

	if (!ReadFile(pFSFileName, fs)) {
		exit(1);
	};

	AddShader(normalShaderProg, vs.c_str(), GL_VERTEX_SHADER);
	AddShader(normalShaderProg, fs.c_str(), GL_FRAGMENT_SHADER);

	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };

	glLinkProgram(normalShaderProg);
	glGetProgramiv(normalShaderProg, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(normalShaderProg, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	glValidateProgram(normalShaderProg);
	glGetProgramiv(normalShaderProg, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(normalShaderProg, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	glUseProgram(normalShaderProg);
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

