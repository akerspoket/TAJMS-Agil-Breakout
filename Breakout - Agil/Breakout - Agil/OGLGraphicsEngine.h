#pragma once
#include <GL\glew.h>
#include <SDL2\SDL.h>
#include "glext.h"
#include "Math.h"
#include "ObjLoader.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <assert.h>
#include <vector>

using namespace std;




class OGLGraphicsEngine
{
public:
	OGLGraphicsEngine();
	~OGLGraphicsEngine();

	int InitGlew(SDL_Window* pWND);
	void CreateTriangle();
	void RenderFrame();
	void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
	void CompileShaders();
	


	vec3 Vertices[3];
	GLuint VBO;
	SDL_Window* mWindow;
	SDL_GLContext m_glContext;
	const char* pVSFileName = "shader.vs";
	const char* pFSFileName = "shader.fs";

private:
	bool ReadFile(const char* pFileName, string& outFile);
	int CreateVertexBuffer(void* pDataStart, int pBufferSize);
	int AddUniform(GLuint pShader, const GLchar* pName);
	vector<GLuint> mBuffers;
	int mVertexBufferID;
	vector<GLuint> mUniforms;
	int mUniformID;
	GLuint normalShaderProg;


};

