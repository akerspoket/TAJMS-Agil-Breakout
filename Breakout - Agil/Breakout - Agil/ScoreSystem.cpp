#include "ScoreSystem.h"
#include "EventManager.h"
#include "LevelManager.h"
#include "EntityManager.h"
#include "ComponentTable.h"
#include "ScoreValueComponent.h"
#include "StorageShelf.h"
#include "PowerUpComponent.h"

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
	mEventManager->Subscribe("Collision", this);
}
void ScoreSystem::Start() 
{

}
void ScoreSystem::Update(double pDeltaTime) 
{
	//Draw the score

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
		SendScore();
		//cout << "Your score is:" << mScore << endl;
	}

	else if (pEvent->mID == "Collision")
	{
		int value = 0;
		
		
		
		if (ComponentTable::GetInstance()->HasComponent(*(EntityID*)pEvent->mPayload["ID1"], SoundCollisionType))
		{
			value += GetComponent<ScoreValueComponent>(*(EntityID*)pEvent->mPayload["ID1"])->value;
		}
		if (ComponentTable::GetInstance()->HasComponent(*(EntityID*)pEvent->mPayload["ID2"], SoundCollisionType))
		{
			value  += GetComponent<ScoreValueComponent>(*(EntityID*)pEvent->mPayload["ID2"])->value;
		}

		if (tCompTable->HasComponent(*(EntityID*)pEvent->mPayload["ID2"], PowerUpType))
		{
			if (GetComponent<PowerUpComponent>(*(EntityID*)pEvent->mPayload["ID2"])->HasPowerUp(BallNet))
			{
				value = 0;
			}
		}

		mScore -= value;

		SendScore();

		//cout << "Your score is:" << mScore << endl;
	}
}

void ScoreSystem::SendScore()
{
	unordered_map<string, void*> payload;
	int* tInt = new int();
	*tInt = mScore;
	payload["score"] = tInt;
	mEventManager->BroadcastEvent("DrawScore", payload);
}