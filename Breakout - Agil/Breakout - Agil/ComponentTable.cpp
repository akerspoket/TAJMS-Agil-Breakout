#include "ComponentTable.h"


ComponentTable* ComponentTable::mSingleton = nullptr;

ComponentTable* ComponentTable::GetInstance()
{
	if (mSingleton == nullptr)
	{
		mSingleton = new ComponentTable();
	}

	return mSingleton;
}

ComponentTable::ComponentTable()
{
	memset(mComponentTable, 0, sizeof(mComponentTable));
}


ComponentTable::~ComponentTable()
{
}

bool ComponentTable::HasComponent(int pEntityID, ComponentType pCompType)
{
	short tLineToCheck = mComponentTable[pEntityID];
	short tMaskToUse = (1 << pCompType); //00000001 to 00000100

	if ((tLineToCheck & tMaskToUse) != 0) //then there is an component
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

	
	if ((tLineToAddTo & tMaskToUse) == 0)
	{
		tLineToAddTo = tLineToAddTo | tMaskToUse;
		mComponentTable[pEntityID] = tLineToAddTo;
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