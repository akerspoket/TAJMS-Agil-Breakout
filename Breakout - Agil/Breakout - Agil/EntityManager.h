#pragma once
#include <list>
#include "Constants.h"




class EntityManager
{
public:
	static EntityManager* GetInstance();

	EntityID AddEntity();
	void RemoveEntity(int pEntityID);

private:
	EntityManager();
	~EntityManager();
	static EntityManager* mSingleton;

	std::list<EntityID> mFreeEntitySlots;
	EntityID mNextSlot;

};

