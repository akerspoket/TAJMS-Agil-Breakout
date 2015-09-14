#include <iostream>
#include "Game1.h"
#include <SDL2\SDL.h>

using namespace std;

Game1 gGame;

int main(int argc, char* args[])
{
	bool tNoError = gGame.Initialize();

	if (tNoError)
		gGame.Run();


	return 0;
}

