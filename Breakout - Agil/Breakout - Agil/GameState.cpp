#include "GameState.h"

GameStateClass* GameStateClass::mSingleton = nullptr;

GameStateClass* GameStateClass::GetInstance()
{
	if (mSingleton == nullptr)
	{
		mSingleton = new GameStateClass();
	}

	return mSingleton;
}


GameStateClass::GameStateClass()
{

}

GameStateClass::~GameStateClass()
{

}