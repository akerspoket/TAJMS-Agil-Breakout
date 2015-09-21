#pragma once
#include <string>
#include "EntityFactory.h"

using namespace std;

class LevelManager
{
public:
	static LevelManager* GetInstance();

	void LevelManager::Initialize();
	void GenerateWorld(string pWorldName);
	void AnalyzeText(string pTextToCheck);
private:
	LevelManager();
	~LevelManager();

	EntityFactory* mEntityFactory;
	static LevelManager* mSingleton;

};

