#include "ComponentTable.h"



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