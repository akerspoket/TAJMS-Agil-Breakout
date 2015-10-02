#pragma once
#include "System.h"
#include <vector>
#include <SDL2/SDL.h>

using namespace std;

class Game1
{
public:
	Game1();
	~Game1();

	//create systems and add them to systemlist, initializes the systems
	bool Initialize();
	void Run();
	void Destroy();

private:
	std::vector<System*> mSystems;
	
};

