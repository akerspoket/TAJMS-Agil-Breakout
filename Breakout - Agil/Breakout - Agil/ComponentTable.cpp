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

bool ComponentTable::HasComponent(int pEntityID, short pMask)
{
	short tLineToCheck = mComponentTable[pEntityID];

	if ((tLineToCheck & pMask) != 0) //then there are the components from mask
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

void ComponentTable::AddComponent(int pEntityID, short pMask)
{
	short tLineToAddTo = mComponentTable[pEntityID];

	
	if ((tLineToAddTo & pMask) == 0)
	{
		tLineToAddTo = tLineToAddTo | pMask;
		mComponentTable[pEntityID] = tLineToAddTo;
	}
	else
	{
		//TODO:: Set Error if we already have component
	}
}

void ComponentTable::RemoveComponent(int pEntityID, short pMask)
{

}

void ComponentTable::RemoveEntity(int pEntityID)
{

}