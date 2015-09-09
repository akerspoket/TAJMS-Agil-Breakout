#pragma once
#include "Constants.h"
#include "PhysicComponent.h"
#include <map>
#include "Shelf.h"

class StorageLibrary
{
public:
	typedef void* Component;

	StorageLibrary();
	~StorageLibrary();

	/*void Initialize();
	void AddComponentArray(ComponentType pComponentType, void* pComponentClass);

	void AddItem();
	void RemoveItem();

	template<class T>
	T GetComponent(int pEntityID, ComponentType pComopnentType);*/

private:

	//std::map<ComponentType, T[MAX_NUM_ENTITIES]> mComponentMap;
	
	//std::map<ComponentType, Shelf> mMaps;

};

