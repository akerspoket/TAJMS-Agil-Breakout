#pragma once
#include <list>
#include "Constants.h"




class EntityManager
{
public:
	static EntityManager* GetInstance();

	EntityID AddEntity();
	void RemoveEntity(int pEntityID);
	const int GetLastEntity() { return mNextSlot; }

private:
	EntityManager();
	~EntityManager();
	static EntityManager* mSingleton;

	std::list<EntityID> mFreeEntitySlots;
	EntityID mNextSlot;

};

