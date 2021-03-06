#include <iostream>
#include "Game1.h"
#include "OGLGraphicsEngine.h"

using namespace std;

Game1 gGame;

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(int argc, char* args[])
{
	//Create window pointer
	SDL_Window* window = NULL;

	

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create window
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		
#ifdef _WIN32//__linux__ //Should be linux and notwindows, windows is for testing
		SDL_GLContext tGLContext; //Should be able to have this in main or somewhere else Y
		tGLContext = SDL_GL_CreateContext(window);

		GLenum res = glewInit();
		if (res != GLEW_OK)
		{
			fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
			return -1;
		}	//To here!	
#endif		

		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			bool tNoError = gGame.Initialize(window);
			if (tNoError)
			{
				gGame.Run();
		/*		while(true)
				mOGLGraphics->RenderFrame();*/
			}
		}
	}
	return 0;
}

