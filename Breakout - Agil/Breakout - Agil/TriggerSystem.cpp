#include "TriggerSystem.h"
#include "EventManager.h"
#include "LevelManager.h"


TriggerSystem::TriggerSystem()
{
}


TriggerSystem::~TriggerSystem()
{
}

void TriggerSystem::Initialize()
{
	mEventManager = mEventManager->GetInstance();
	LevelManager* tLevelManager = tLevelManager->GetInstance();
	tLevelManager->Initialize();
}

void TriggerSystem::Start()
{

}

void TriggerSystem::Update(double pDeltaTime)
{

	//done with level ->remove everything then load new map
	if (true)
	{
		//remove everything

		//load new world
		LevelManager* tLevelManager = tLevelManager->GetInstance();
		tLevelManager->GenerateWorld("FirstWorld");
	}
}

void TriggerSystem::Pause()
{

}

void TriggerSystem::Stop()
{

}

void TriggerSystem::OnEvent(Event* pEvent)
{

}