#include "ComponentTable.h"


ComponentTable* ComponentTable::mSingleton = nullptr;

ComponentTable* ComponentTable::GetInstance()
{
	if (mSingleton == nullptr)
	{
		mSingleton = new ComponentTable();
	}

	return nullptr;
}

ComponentTable::ComponentTable()
{
}


ComponentTable::~ComponentTable()
{
}

bool ComponentTable::HasComponent(int pEntityID, ComponentType pCompType)
{
	short tLineToCheck = mComponentTable[pEntityID];
	short tMaskToUse = (1 << pCompType);

	if (tLineToCheck & tMaskToUse != 0) //then there is an component
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ComponentTable::AddComponent(int pEntityID, ComponentType pCompType)
{
	short tLineToAddTo = mComponentTable[pEntityID];
	short tMaskToUse = (1 << pCompType);

	
	if (tLineToAddTo & tMaskToUse == 0) //then there is an component
	{
		tLineToAddTo = tLineToAddTo | tMaskToUse;
	}
	else
	{
		//TODO:: Set Error if we already have component
	}
}

void ComponentTable::RemoveComponent(int pEntityID, ComponentType pCompType)
{

}

void ComponentTable::RemoveEntity(int pEntityID)
{

}