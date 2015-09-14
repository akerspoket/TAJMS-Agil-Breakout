#include <iostream>
#include "Game1.h"
#include "EntityFactory.h"
#include "PhysicComponent.h"
#include "TransformComponent.h"
#include "StorageShelf.h"


using namespace std;

Game1 gGame;

int main()
{
	bool tNoError = gGame.Initialize();

	if (tNoError)
		gGame.Run();


	return 0;
}

