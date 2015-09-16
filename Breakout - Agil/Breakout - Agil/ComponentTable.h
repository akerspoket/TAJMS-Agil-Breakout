#pragma once
#include "Constants.h"
#include <string>

//bit lines for each entity
//1 if have component, 0 if not
class ComponentTable
{
public:
	static ComponentTable* GetInstance();
	
	bool HasComponent(int pEntityID, short pMask);
	void AddComponent(int pEntityID, short pMask);
	void RemoveComponent(int pEntityID, short pMask);
	void RemoveEntity(int pEntityID);


private:
	ComponentTable();
	~ComponentTable();
	static ComponentTable* mSingleton;

	short mComponentTable[MAX_NUM_ENTITIES];
};

