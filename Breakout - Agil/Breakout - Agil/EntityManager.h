#pragma once
#include <list>

#define EntityID int


class EntityManager
{
public:
	static EntityManager* GetInstance();

	int AddEntity();
	void RemoveEntity(int pEntityID);

private:
	EntityManager();
	~EntityManager();
	static EntityManager* mSingleton;

	std::list<EntityID> mFreeEntitySlots;
	EntityID mNextSlot;

};

