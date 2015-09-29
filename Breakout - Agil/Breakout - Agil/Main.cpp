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
	OGLGraphicsEngine* mOGLGraphics = new OGLGraphicsEngine();


	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create window
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);


		mOGLGraphics->InitGlew(window);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			bool tNoError = gGame.Initialize();
			if (tNoError)
			{
				//gGame.Run();
				while (true)
					mOGLGraphics->RenderFrame();
			}
		}
	}
	return 0;
}

