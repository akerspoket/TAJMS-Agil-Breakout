#pragma once
#include "Constants.h"

template<class T>
class StorageShelf
{
public:
	static StorageShelf<T>* GetInstance();

private:
	StorageShelf();
	~StorageShelf();

	static StorageShelf<T>* mSingleton;
	T mItems[MAX_NUM_ENTITIES];
};

//This is the magic about singletons
//Find the right shelf for the needed component
template<class T>
static T* GetComponent(EntityID pEntityID)
{
	StorageShelf<T>* tNeededShelf = tNeededShelf->GetInstance();

	return tNeededShelf[pEntityID];
}