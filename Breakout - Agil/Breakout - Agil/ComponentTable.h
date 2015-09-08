#pragma once
#include "Constants.h"

class ComponentTable
{
public:
	static ComponentTable* GetInstance();
	
	bool HasComponent(int pEntityID, ComponentType pCompType);
	void AddComponent(int pEntityID, ComponentType pCompType);
	void RemoveComponent(int pEntityID, ComponentType pCompType);
	void RemoveEntity(int pEntityID);


private:
	ComponentTable();
	~ComponentTable();
	static ComponentTable* mSingleton;

	short mComponentTable[MAX_NUM_ENTITIES];
};

