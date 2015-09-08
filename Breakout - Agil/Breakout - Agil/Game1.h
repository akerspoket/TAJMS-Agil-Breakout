#pragma once
#include "System.h"
#include <vector>

class Game1
{
public:
	Game1();
	~Game1();
	bool Initialize();
	void Run();
	void Destroy();

private:
	std::vector<System*> mSystems;
};

