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
	void DegenerateMenu();
	void DegenerateEverything();
	void AnalyzeText(string pTextToCheck);
	void GenerateMainMenu();
	void GenerateDeathScreen();
	void GeneratePauseScreen();
private:
	LevelManager();
	~LevelManager();

	EntityFactory* mEntityFactory;
	static LevelManager* mSingleton;

};

