#include "ScoreSystem.h"
#include "EventManager.h"
#include "LevelManager.h"
#include "EntityManager.h"
#include "ComponentTable.h"


ScoreSystem::ScoreSystem()
{
	mScore = 0;
}

ScoreSystem::ScoreSystem(string pName) :System(pName)
{
	mScore = 0;
}

ScoreSystem::~ScoreSystem()
{
}

void ScoreSystem::Initialize()
{
	mEventManager = mEventManager->GetInstance();
	mEventManager->Subscribe("SetScore", this);
}
void ScoreSystem::Start() 
{

}
void ScoreSystem::Update(double pDeltaTime) 
{
	//Draw the score
	cout << mScore << endl;

}
void ScoreSystem::Pause() 
{

}
void ScoreSystem::Stop() 
{

}
void ScoreSystem::OnEvent(Event* pEvent) 
{
	EntityManager* tEntMan = tEntMan->GetInstance();
	ComponentTable* tCompTable = tCompTable->GetInstance();

	if (pEvent->mID == "SetScore")
	{
		mScore = *(int*)pEvent->mPayload["score"];
	}
}
