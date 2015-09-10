#include "StorageShelf.h"


template<class T>
StorageShelf<T>* StorageShelf<T>::mSingleton = nullptr;

template<class T>
StorageShelf<T>* StorageShelf<T>::GetInstance()
{
	if (mSingleton == null)
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
