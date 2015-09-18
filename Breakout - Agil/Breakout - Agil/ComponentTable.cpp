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

	if ((tLineToCheck ^ pMask) != 0) //then there are the components from mask
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

	
	tLineToAddTo = tLineToAddTo | pMask;
	mComponentTable[pEntityID] = tLineToAddTo;

}

void ComponentTable::RemoveComponent(int pEntityID, short pMask)
{

}

void ComponentTable::RemoveEntity(int pEntityID)
{
	mComponentTable[pEntityID] = 0;
}