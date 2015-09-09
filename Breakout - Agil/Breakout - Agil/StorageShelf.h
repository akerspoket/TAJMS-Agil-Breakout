#pragma once
#include "Constants.h"
#include "Component.h"
#include "PhysicComponent.h"
#include <map>

class StorageShelf
{
public:
	StorageShelf();
	~StorageShelf();

	void Initialize();
	void AddComponentArray();

	void AddItem();
	void RemoveItem();
	Component* GetComponent(int pEntityID, ComponentType);

private:


	//std::map<Component[], ComponentType> mComponentMap;

};

