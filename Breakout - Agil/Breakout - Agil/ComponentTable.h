#pragma once
#include "Constants.h"

class ComponentTable
{
public:
	ComponentTable();
	~ComponentTable();
	
	bool HasComponent(int pEntityID, ComponentType pCompType);


private:
	short mComponentTable[MAX_NUM_ENTITIES];
};

