#include "EntityManager.h"

EntityManager* EntityManager::mSingleton = nullptr;

EntityManager* EntityManager::GetInstance()
{
	if (mSingleton == nullptr)
	{
		mSingleton = new EntityManager();
	}
	return mSingleton;
}

EntityManager::EntityManager()
{
	mNextSlot = 0;
}


EntityManager::~EntityManager()
{
}

EntityID EntityManager::AddEntity()
{
	EntityID tIDToUse;

	//if any free slots we use them
	if (mFreeEntitySlots.size() != 0)
	{
		tIDToUse = mFreeEntitySlots.back();
		mFreeEntitySlots.pop_back();
	}
	else
	{
		tIDToUse = mNextSlot;
		mNextSlot++;
	}
	return tIDToUse;
}

void EntityManager::RemoveEntity(int pEntityID)
{
	//not sure how we are to define how an entity doesn't exist, if we have a table to show if it exist, or just that
	//if we have it as no components exist in a table? 

	//TODO: Remove from table

	mFreeEntitySlots.push_back(pEntityID);
}
