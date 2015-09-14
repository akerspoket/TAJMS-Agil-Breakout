#pragma once
#include <string>
#include <map>
#include "Constants.h"
#include <vector>

using namespace std;

class EntityFactory
{
public:
	typedef std::map<ComponentType, void*> EntityBlueprint;

	static EntityFactory* GetInstance();

	void Initialize();
	void RegisterEntityTemplate(string pName, EntityBlueprint pComponents);
	EntityID CreateEntity(std::string pTemplateName);



private:
	EntityFactory();
	~EntityFactory();
	static EntityFactory* mSingleton;

	

	std::map<string, EntityBlueprint> mEntityBlueprints;
};

