#include "OGLGraphicsEngine.h"


OGLGraphicsEngine::OGLGraphicsEngine()
{
}


OGLGraphicsEngine::~OGLGraphicsEngine()
{
}


int OGLGraphicsEngine::InitGlew(SDL_Window* pWND)
{
	mWindow = pWND;// SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 800, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//SDL_GLContext tGLContext; //Should be able to have this in main or somewhere else Y
	//tGLContext = SDL_GL_CreateContext(pWND);

	//GLenum res = glewInit();
	//if (res != GLEW_OK)
	//{
	//	fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
	//	return -1;
	//}	//To here!																	V
	mObjLoader = new ObjLoader();
	glEnable(GL_DEPTH_TEST);
	printf("GL version: %s\n", glGetString(GL_VERSION));
	//CreateTriangle();
	//Vertices = mObjLoader->LoadObj("bth.obj", vec3(0.03f, 0.03f, 0.03f));


	//mVertexBufferID = CreateObjectBuffer(Vertices.data(), sizeof(Vertex)*Vertices.size(), Vertices.size());
	CompileShaders();
	//InitGraphics(45.0f, 600.0f, 800.0f, 0.1f, 100, 13.0f);
	//int result = SDL_GL_SetSwapInterval(1); //Laggs really much if vsync is active, should be something better


	return 1;
}

void OGLGraphicsEngine::InitGraphics(float pFoVAngleY, float pHeight, float pWidth, float pNear, float pFar, float pZPos)
{
	mWVPBuffer.world = glm::mat4();
	mWVPBuffer.view = glm::lookAt(glm::vec3(0.0f, 0.0f, pZPos),glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0, 1, 0));
	mWVPBuffer.projection = glm::perspective(pFoVAngleY, pWidth / pHeight, pNear, pFar);

	mWVPBufferID = AddUniform(mNormalShaderProg, "gWorld");
	glUniformMatrix4fv(mUniforms[mWVPBufferID], 1, GL_FALSE, (float*)&mWVPBuffer.world);
	mWVPBufferID = AddUniform(mNormalShaderProg, "gView");
	glUniformMatrix4fv(mUniforms[mWVPBufferID], 1, GL_FALSE, (float*)&mWVPBuffer.view);
	mWVPBufferID = AddUniform(mNormalShaderProg, "gProj");
	glUniformMatrix4fv(mUniforms[mWVPBufferID], 1, GL_FALSE, (float*)&mWVPBuffer.projection);

	mTransMatricesUniformID = AddUniform(mNormalShaderProg, "gTransMatrices");
	//glUniformMatrix4fv(mUniforms[mTransMatricesUniformID], 1, GL_FALSE, (float*)&mWVPBuffer.world);

	//För instanceDraw
	mTransBuffer = CreateVertexBuffer(nullptr, 0);
	InitText2D();

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

void OGLGraphicsEngine::ChangeTextBuffer(void* pDataStart, int pDataSize, int pNumberOfIndices, GLuint pIndex)
{
	glBindBuffer(GL_ARRAY_BUFFER, pIndex);
	glBufferData(GL_ARRAY_BUFFER, pDataSize, pDataStart, GL_STATIC_DRAW);
}


int OGLGraphicsEngine::AddUniform(GLuint pShader, const GLchar* pName)
{
	glUseProgram(pShader);
	GLuint tTempUniformLocation = glGetUniformLocation(pShader, pName);
	assert(tTempUniformLocation != 0xFFFFFFFF);
	mUniforms.push_back(tTempUniformLocation);
	return mUniforms.size() - 1;

}

int OGLGraphicsEngine::CreateTexture(const char *pFileName)
{
	GLuint tTexture;
	glGenTextures(1, &tTexture);
	glBindTexture(GL_TEXTURE_2D, tTexture);
	unsigned char* ht_map;
	int width, height;
	//char* derp = new char;
	//wcstombs(derp, pFileName, 128);
	
	ht_map = SOIL_load_image
		(
			pFileName,
			&width, &height, 0,
			SOIL_LOAD_RGBA
			);
	const char* res = SOIL_last_result();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, ht_map);//kanske dra in alpha i andra gl_RGB //2048 är widith å height
	SOIL_free_image_data(ht_map);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT); //vad gör alla wrapsen? mitt projekt hade bara S
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	mTextures.push_back(tTexture);
	return mTextures.size()-1;

}

void OGLGraphicsEngine::InitText2D() {

	// Initialize texture
	mText2DTextureID = CreateTexture("Textures/Letters.png");

	// Initialize VBO
	glGenBuffers(1, &mText2DVertexBufferID);
	glGenBuffers(1, &mText2DUVBufferID);

	// Initialize Shader
	glUseProgram(mText2DShaderID);
	// Get a handle for our buffers
	mVertexPosition_screenspaceID = glGetAttribLocation(mText2DShaderID, "vertexPosition_screenspace");
	mVertexUVID = glGetAttribLocation(mText2DShaderID, "vertexUV");

	// Initialize uniforms' IDs
	mText2DUniformID = glGetUniformLocation(mText2DShaderID, "myTextureSampler");

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

	
	for (size_t i = 0; i < 4; i++)
	{
		InstanceBufferType tTransMat;
		tTransMat.TranslationMatrices = glm::translate(glm::vec3((float)i*4.0f*sin(Scale), 1.0f, 1.0f));
		mInstanceMatricesTemp.push_back(tTransMat);
		DrawObjects(mVertexBufferID, mInstanceMatricesTemp, i%2);
		mInstanceMatricesTemp.clear();
	}

}


int OGLGraphicsEngine::CreateText(string pText, vec2 pPosition, int size, int pIndex) 
{
	TextType tTextType;
	vector<TextVertex> tTextVertices;

	tTextVertices = mObjLoader->LoadTextVertices(pText.c_str(), pPosition.x, pPosition.y, size);
	mTextTypeBuffer[pIndex].numberOfIndices = tTextVertices.size();
	mTextTypeBuffer[pIndex].size = size;
	mTextTypeBuffer[pIndex].position = pPosition;
	mTextTypeBuffer[pIndex].text = pText;
	ChangeTextBuffer(tTextVertices.data(), tTextVertices.size()*sizeof(TextVertex), tTextVertices.size(), mTextTypeBuffer[pIndex].bufferHandleID);

	return pIndex;
}

void OGLGraphicsEngine::DrawObjects(int pMeshType, vector<InstanceBufferType> pInstanceBufferData, int pTextureBuffer)
{

	glUseProgram(mNormalShaderProg);

	GLuint tTransLoc1 = glGetUniformLocation(mNormalShaderProg, "gTransMatrices");


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mTextures[pTextureBuffer]);

	glBindBuffer(GL_ARRAY_BUFFER, mBuffers[mTransBuffer]);
	glBufferData(GL_ARRAY_BUFFER, pInstanceBufferData.size()* sizeof(InstanceBufferType), pInstanceBufferData.data(), GL_STATIC_DRAW);
	GLuint tPosLoc = glGetAttribLocation(mNormalShaderProg, "Position");
	GLuint tTexLoc = glGetAttribLocation(mNormalShaderProg, "TexCoord");
	GLuint tNormLoc = glGetAttribLocation(mNormalShaderProg, "Normal");
	//GLuint tTransLoc = glGetAttribLocation(mNormalShaderProg, "Translation");
	glEnableVertexAttribArray(tPosLoc);
	glEnableVertexAttribArray(tTexLoc);
	//glEnableVertexAttribArray(tTransLoc);
	glBindBuffer(GL_ARRAY_BUFFER, mObjectBuffers[pMeshType].BufferHandle);
	glVertexAttribPointer(tPosLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(tTexLoc, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(tNormLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(5 * sizeof(float)));
	for (int i = 0; i < pInstanceBufferData.size(); i++)
	{
		glUniformMatrix4fv(tTransLoc1, 1, GL_FALSE, (float*)&pInstanceBufferData[i]);
		glDrawArrays(GL_TRIANGLES, 0, mObjectBuffers[pMeshType].NumberOfIndices);
	}
	//glDrawArraysInstanced(GL_TRIANGLES, 0, mObjectBuffers[pMeshType].NumberOfIndices, pInstanceBufferData.size());
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	//glDisableVertexAttribArray(3);
	//glDisableVertexAttribArray(4);
	//glDisableVertexAttribArray(5);
	//glDisableVertexAttribArray(6);



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
	mText2DShaderID = glCreateProgram();

	if (mNormalShaderProg == 0) {
		fprintf(stderr, "Error creating shader program\n");
		int hi;
		std::cin >> hi;
	}

	std::string vs, fs, textvs, textfs;

	if (!ReadFile(pVSFileName, vs)) {
		exit(1);
	};

	if (!ReadFile(pFSFileName, fs)) {
		exit(1);
	};

	if (!ReadFile(pTextVSFileName, textvs)) {
		exit(1);
	};
	if (!ReadFile(pTextFSFileName, textfs)) {
		exit(1);
	};


	AddShader(mNormalShaderProg, vs.c_str(), GL_VERTEX_SHADER);
	AddShader(mNormalShaderProg, fs.c_str(), GL_FRAGMENT_SHADER);

	AddShader(mText2DShaderID, textvs.c_str(), GL_VERTEX_SHADER);
	AddShader(mText2DShaderID, textfs.c_str(), GL_FRAGMENT_SHADER);

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


	glLinkProgram(mText2DShaderID);
	glGetProgramiv(mText2DShaderID, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(mText2DShaderID, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program for Text: '%s'\n", ErrorLog);
		int hi;
		std::cin >> hi;
	}


	glValidateProgram(mText2DShaderID);
	glGetProgramiv(mText2DShaderID, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(mText2DShaderID, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Invalid shader program for Text: '%s'\n", ErrorLog);
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

int OGLGraphicsEngine::CreateObject(string pMeshName)
{
	vector<Vertex> tVertices;
	if (pMeshName == "Object/Block.obj")
	{
		tVertices = mObjLoader->LoadObj(pMeshName, vec3(1.0f, 1.0f, 1.0f));
	}
	else if (pMeshName == "Object/Pad.obj")
	{
		tVertices = mObjLoader->LoadObj(pMeshName, vec3(2.0f, 0.5f, 1.0f));
	}
	else if (pMeshName == "Object/Boll.obj")
	{
		tVertices = mObjLoader->LoadObj(pMeshName, vec3(0.5f, 0.5f, 0.5f));
	}
	else if (pMeshName == "Object/Background.obj")
	{
		tVertices = mObjLoader->LoadObj(pMeshName, vec3(40.0f, 40.0f, 0.2f));
	}
	else if (pMeshName == "Object/SideWall.obj")
	{
		tVertices = mObjLoader->LoadObj(pMeshName, vec3(3.0f, 30.0f, 0.02f));
	}
	else
	{
		tVertices = mObjLoader->LoadObj(pMeshName, vec3(1.0f, 1.0f, 1.0f));
	}

	int retValue = CreateObjectBuffer(tVertices.data(), sizeof(Vertex)*tVertices.size(), tVertices.size());

	return retValue;
}

void OGLGraphicsEngine::EndDraw()
{	
	SDL_GL_SwapWindow(mWindow);
	glClearColor(0.0f, 0.2f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OGLGraphicsEngine::DrawText(int pTextID)
{
	glUseProgram(mText2DShaderID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mTextures[mText2DTextureID]);
	// Set our "myTextureSampler" sampler to user Texture Unit 0
	glUniform1i(mText2DUniformID, 0);

	glEnableVertexAttribArray(mVertexPosition_screenspaceID);
	glEnableVertexAttribArray(mVertexUVID);
	glBindBuffer(GL_ARRAY_BUFFER, mTextTypeBuffer[pTextID].bufferHandleID);
	glVertexAttribPointer(mVertexPosition_screenspaceID, 2, GL_FLOAT, GL_FALSE, sizeof(TextVertex), (void*)0);
	glVertexAttribPointer(mVertexUVID, 2, GL_FLOAT, GL_FALSE, sizeof(TextVertex), (void*)(2 * sizeof(float)));

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_ONE, GL_ONE);

	// Draw call
	glDrawArrays(GL_TRIANGLES, 0, mTextTypeBuffer[pTextID].numberOfIndices);

	glDisable(GL_BLEND);

	glDisableVertexAttribArray(mVertexPosition_screenspaceID);
	glDisableVertexAttribArray(mVertexUVID);

}

int OGLGraphicsEngine::CreateNewText(int pMaxCharacters)
{
	TextType tText;
	GLuint tTempBuffer;
	glGenBuffers(1, &tTempBuffer);
	tText.bufferHandleID = tTempBuffer;
	tText.numberOfIndices = 0;
	tText.position = vec2(0, 0);
	tText.size = 0;
	tText.text = "";
	mTextTypeBuffer.push_back(tText);
	return mTextTypeBuffer.size() - 1;
}
void OGLGraphicsEngine::DrawThisText(string pText, vec2 pPosition, float pSize, int pSentenceID)
{
	if (pText != mTextTypeBuffer[pSentenceID].text || pPosition != mTextTypeBuffer[pSentenceID].position || pSize != mTextTypeBuffer[pSentenceID].size)
	{
		CreateText(pText, pPosition, pSize, pSentenceID);
	}
	glUseProgram(mText2DShaderID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mTextures[mText2DTextureID]);
	// Set our "myTextureSampler" sampler to user Texture Unit 0
	glUniform1i(mText2DUniformID, 0);

	glEnableVertexAttribArray(mVertexPosition_screenspaceID);
	glEnableVertexAttribArray(mVertexUVID);

	glBindBuffer(GL_ARRAY_BUFFER, mTextTypeBuffer[pSentenceID].bufferHandleID);
	glVertexAttribPointer(mVertexPosition_screenspaceID, 2, GL_FLOAT, GL_FALSE, sizeof(TextVertex), (void*)0);
	glVertexAttribPointer(mVertexUVID, 2, GL_FLOAT, GL_FALSE, sizeof(TextVertex), (void*)(2 * sizeof(float)));

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_ONE, GL_ONE);

	// Draw call
	glDrawArrays(GL_TRIANGLES, 0, mTextTypeBuffer[pSentenceID].numberOfIndices);

	glDisable(GL_BLEND);

	glDisableVertexAttribArray(mVertexPosition_screenspaceID);
	glDisableVertexAttribArray(mVertexUVID);
}