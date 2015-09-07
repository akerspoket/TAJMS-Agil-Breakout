#include <iostream>
#include "Game1.h"

using namespace std;

Game1 gGame;

int main()
{
	bool t_NoError = gGame = gGame.Initialize();

	if (t_NoError)
		gGame.Run();


	return 0;
}

