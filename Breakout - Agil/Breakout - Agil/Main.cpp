#include <iostream>
#include "Game1.h"
#include "WindowCreator.h"

using namespace std;

Game1 gGame;

int main()
{
	bool tNoError = gGame.Initialize();
	WindowCreator winc = WindowCreator();
	winc.WinMain(0, 0, 0, 1);
	if (tNoError)
		gGame.Run();




	return 0;
}

