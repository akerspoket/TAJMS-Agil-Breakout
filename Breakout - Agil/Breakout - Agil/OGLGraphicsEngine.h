#pragma once
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include "glext.h"
#include "Math.h"
#include "ObjLoader.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <assert.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <SOIL/SOIL.h>


using namespace std;

struct TextType
{
	int numberOfIndices;
	int bufferHandleID;
	string text;
};

struct MatrixBufferType
{
	glm::mat4 world;
	glm::mat4 view;
	glm::mat4 projection;
};

struct ObjectBufferType
{
	GLuint BufferHandle;
	GLuint NumberOfIndices;

};

struct InstanceBufferType
{
	glm::mat4 TranslationMatrices;
};

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
	void InitGraphics(float pFoVAngleY, float pHeight, float pWidth, float pNear, float pFar, float pZPos);
	void DrawObjects(int pMeshType, vector<InstanceBufferType> pInstanceBufferData, int pTextureBuffer);
	void DrawText(int pTextID);
	int CreateObjectBuffer(void* pDataStart, int pDataSize, int pNumberOfIndices);
	int CreateTexture(const char *pFileName);
	int CreateObject(string pMeshName);
	int CreateText(const char* pText, int x, int y, int size, int pIndex);
	void EndDraw();
	void ChangeObjectBuffer(void* pDataStart, int pDataSize, int pNumberOfIndices, int pIndex);
	void printText2D(const char * text, int x, int y, int size);
	glm::mat4x4 mProjMat;

	vector< Vertex >Vertices;
	GLuint VBO;
	SDL_Window* mWindow;
	SDL_GLContext m_glContext;
	const char* pVSFileName = "shader.vs";
	const char* pFSFileName = "shader.fs";

	const char* pTextVSFileName = "textshader.vs";
	const char* pTextFSFileName = "textshader.fs";

private:
	bool ReadFile(const char* pFileName, string& outFile);
	int CreateVertexBuffer(void* pDataStart, int pBufferSize);
	int AddUniform(GLuint pShader, const GLchar* pName);
	vector<GLuint> mBuffers;

	void InitText2D();
	void cleanupText2D();

	string prevScore;
	vector<TextVertex> mTextVertices;
	vector<GLuint> mTextBuffers;
	int mtextID;


	vector<TextType> mTextTypeBuffer;
	vector<GLuint> mTextures;

	int mTextureID;
	int mTextureID2;

	vector<ObjectBufferType> mObjectBuffers;
	int mVertexBufferID;
	vector<GLuint> mUniforms;
	int mUniformID;
	GLuint mNormalShaderProg;
	ObjLoader* mObjLoader;
	MatrixBufferType mWVPBuffer;
	int mWVPBufferID;
	GLuint mTransBuffer;

	//Temp things only for testing withouth rest
	vector<InstanceBufferType> mInstanceMatricesTemp;
	GLuint mTransMatricesUniformID;


	GLuint mText2DTextureID;              // Texture containing the font
	GLuint mText2DVertexBufferID;         // Buffer containing the vertices
	GLuint mText2DUVBufferID;             //                       UVs
	GLuint mText2DShaderID;               // Program used to disaply the text
	GLuint mVertexPosition_screenspaceID; // Location of the program's "vertexPosition_screenspace" attribute
	GLuint mVertexUVID;                   // Location of the program's "vertexUV" attribute
	GLuint mText2DUniformID;              // Location of the program's texture attribute



};

