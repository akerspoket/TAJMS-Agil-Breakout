#include "OGLGraphicsEngine.h"



OGLGraphicsEngine::OGLGraphicsEngine()
{


	InitGlew();
	CreateTriangle();
}


OGLGraphicsEngine::~OGLGraphicsEngine()
{
}


int OGLGraphicsEngine::InitGlew()
{

	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return -1;
	}
	return 1;
}

void OGLGraphicsEngine::CreateTriangle()
{
	Vertices[0] = vec3(-0.3f, -0.3f, 0.0f);
	Vertices[1] = vec3(0.0f, 0.3f, 0.0f);
	Vertices[2] = vec3(0.3f, -0.3f, 0.0f);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

}

void OGLGraphicsEngine::RenderFrame()
{



}