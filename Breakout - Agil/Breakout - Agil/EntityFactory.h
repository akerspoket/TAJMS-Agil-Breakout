#pragma once
#include <string>
#include <map>
#include "Constants.h"
#include <vector>

using namespace std;

class EntityFactory
{
public:
	static EntityFactory* GetInstance();

	void Initialize();
	void RegisterEntityTemplate(map<string, vector<string>> pEntityString);
	EntityID CreateEntity(std::string pTemplateName);



private:
	EntityFactory();
	~EntityFactory();
	static EntityFactory* mSingleton;

	typedef std::map<ComponentType, void*> EntityBlueprint;

	std::map<string, EntityBlueprint*> mEntityBlueprints;
};

