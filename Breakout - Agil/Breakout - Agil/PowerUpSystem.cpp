#include "PowerUpSystem.h"
#include "EventManager.h"
#include "EntityManager.h"
#include "ComponentTable.h"
#include "StorageShelf.h"
#include "VelocityComponent.h"
#include "PowerUpComponent.h"

PowerUpSystem::PowerUpSystem()
{
}

PowerUpSystem::PowerUpSystem(string pName) :System(pName)
{

}


PowerUpSystem::~PowerUpSystem()
{
}

void PowerUpSystem::Initialize()
{
	EventManager::GetInstance()->Subscribe("PowerUpPickedUp", this);
}
void PowerUpSystem::Start() {}
void PowerUpSystem::Update(double pDeltaTime)
{
	EntityManager* tEntManager = tEntManager->GetInstance();
	ComponentTable* tCompTable = tCompTable->GetInstance();
	int tMaxEnt = tEntManager->GetLastEntity();

	//Iterate through all entities
	for (int i = 0; i < tMaxEnt; i++)
	{
		if (tCompTable->HasComponent(i, PowerUpType))
		{
			PowerUpComponent* tPup = GetComponent<PowerUpComponent>(i);
			//Subtract time from durations
			for (int j = 0; j < NumPowerUps; j++)
			{
				tPup->timers[j] -= pDeltaTime;
				//Check if timer ran out
				if (tPup->timers[j] <= 0)
				{
					RemovePower(i, j);
				}
			}
		}

	}

}
void PowerUpSystem::Pause() {}
void PowerUpSystem::Stop() {}
void PowerUpSystem::OnEvent(Event* pEvent)
{
	EntityManager* tEntMan = tEntMan->GetInstance();
	ComponentTable* tCompTable = tCompTable->GetInstance();

	if (pEvent->mID == "PowerUpPickedUp")
	{
		EntityID entID = *(EntityID*)pEvent->mPayload["EntityID"];
		short mask = *(short*)pEvent->mPayload["mask"];
  		float duration = *(float*)pEvent->mPayload["duration"];

		GetComponent<PowerUpComponent>(entID)->AddPowerUp(mask);
		
		tCompTable->AddComponent(entID, PowerUpType);

		switch (mask)
		{
		case SpeedUp:
			GetComponent<VelocityComponent>(entID)->mSpeed *= 3;
			GetComponent<PowerUpComponent>(entID)->timers[SpeedUpLoc] = duration;
			break;
		}
	}
}

void PowerUpSystem::RemovePower(EntityID id, short timerLocation)
{
	ComponentTable* tCompTable = tCompTable->GetInstance();
	GetComponent<PowerUpComponent>(id)->timers[timerLocation] = 0;


	switch (timerLocation)
	{
		case SpeedUpLoc:
			if (GetComponent<PowerUpComponent>(id)->HasPowerUp(SpeedUp))
			{
				GetComponent<VelocityComponent>(id)->mSpeed /= 3;
				GetComponent<PowerUpComponent>(id)->RemovePowerUp(SpeedUp);
			}
			break;
	}
}