#pragma once
#include <string>
#include <map>
#include "Constants.h"
#include <vector>
#include "Component.h"

class EntityFactory
{
public:
	static EntityFactory* GetInstance();

	void Initialize();
	EntityID CreateEntity(std::string pTemplateName);



private:
	EntityFactory();
	~EntityFactory();
	static EntityFactory* mSingleton;

	/*typedef std::map<std::string, std::vector<Component*>> EntityMap;
	EntityMap mMap;*/

};

