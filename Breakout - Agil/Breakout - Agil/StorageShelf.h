#pragma once
#include "Constants.h"

struct componentA
{
	int a;
};

template<class T>
class StorageShelf
{
public:
	static StorageShelf<T>* GetInstance();
	T mItems[MAX_NUM_ENTITIES];

private:
	StorageShelf();
	~StorageShelf();

	static StorageShelf<T>* mSingleton;
	
};

template<class T>
StorageShelf<T>* StorageShelf<T>::mSingleton = nullptr;

template<class T>
StorageShelf<T>* StorageShelf<T>::GetInstance()
{
	if (mSingleton == nullptr)
	{
		mSingleton = new StorageShelf<T>();
	}

	return mSingleton;
}


template<class T>
StorageShelf<T>::StorageShelf<T>()
{
}

template<class T>
StorageShelf<T>::~StorageShelf<T>()
{
}


//This is the magic about singletons
//Find the right shelf for the needed component
template<class T>
static T* GetComponent(EntityID pEntityID)
{
	StorageShelf<T>* tNeededShelf = tNeededShelf->GetInstance();

	return &tNeededShelf->mItems[pEntityID];
}