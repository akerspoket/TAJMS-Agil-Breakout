#pragma once
#include "Constants.h"

class ComponentTable
{
public:
	ComponentTable();
	~ComponentTable();
	
	bool HasComponent(int pEntityID, ComponentType pCompType);
	void AddComponent(int pEntityID, ComponentType pCompType);
	void RemoveComponent(int pEntityID, ComponentType pCompType);
	void ComponentTable::RemoveEntity(int pEntityID);


private:
	short mComponentTable[MAX_NUM_ENTITIES];
};

