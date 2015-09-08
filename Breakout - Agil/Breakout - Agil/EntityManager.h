#pragma once
#include <list>

#define EntityID int


class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	int AddEntity();
	void RemoveEntity(int pEntityID);

private:
	std::list<EntityID> mFreeEntitySlots;
	EntityID mNextSlot;

};

