#include <SDL2\SDL.h>
#include <GL/glew.h>
#include "Math.h"
#include <iostream>

#pragma once
class OGLGraphicsEngine
{
public:
	OGLGraphicsEngine();
	~OGLGraphicsEngine();

	int InitGlew();
	void CreateTriangle();
	void RenderFrame();

	vec3 Vertices[3];
	GLuint VBO;
	SDL_Window* mWindow;
	SDL_GLContext m_glContext;
};

