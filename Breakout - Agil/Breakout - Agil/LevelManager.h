#pragma once
#include <string>
#include "EntityFactory.h"

using namespace std;

class LevelManager
{
public:
	static LevelManager* GetInstance();

	void Initialize();
	void GenerateWorld(string pWorldName);
	void DegenerateWorld();
	void AnalyzeText(string pTextToCheck);
private:
	LevelManager();
	~LevelManager();

	EntityFactory* mEntityFactory;
	static LevelManager* mSingleton;

};

