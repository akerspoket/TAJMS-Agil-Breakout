#include "PowerUpSystem.h"
#include "EventManager.h"
#include "EntityManager.h"
#include "ComponentTable.h"
#include "StorageShelf.h"
#include "VelocityComponent.h"
#include "PowerUpComponent.h"
#include "PowerUpContainComponent.h"
#include "LabelComponent.h"

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
void PowerUpSystem::BallNetPowerUp(float pTime)
{
	EntityManager* tEntManager = tEntManager->GetInstance();
	ComponentTable* tCompTable = tCompTable->GetInstance();
	int tMaxEnt = tEntManager->GetLastEntity();

	for (size_t i = 0; i < tMaxEnt; i++)
	{
		if (tCompTable->HasComponent(i, LabelType))
		{
			if (GetComponent<LabelComponent>(i)->mLabel==Label::Ball)
			{
				GetComponent<PowerUpComponent>(i)->timers[BallNetLoc] = pTime;
			}
		}
	}

	//test
	

}
void PowerUpSystem::OnEvent(Event* pEvent)
{
	EntityManager* tEntMan = tEntMan->GetInstance();
	ComponentTable* tCompTable = tCompTable->GetInstance();

	if (pEvent->mID == "PowerUpPickedUp")
	{
		EntityID entID = *(EntityID*)pEvent->mPayload["EntityID"];
		EntityID pupID = *(EntityID*)pEvent->mPayload["PupEntityID"];

		PowerUpContainComponenet* pupContain = GetComponent<PowerUpContainComponenet>(pupID);


		short mask = pupContain->type;
		float duration = pupContain->duration;

		//need to zero the memory 
		if (!tCompTable->HasComponent(entID, PowerUpType))
		{
			*GetComponent<PowerUpComponent>(entID) = PowerUpComponent();
		}
		tCompTable->AddComponent(entID, PowerUpType);

		GetComponent<PowerUpComponent>(entID)->AddPowerUp(mask);
		
		

		switch (mask)
		{
		case SpeedUp:
			GetComponent<VelocityComponent>(entID)->mSpeed *= 3;
			GetComponent<PowerUpComponent>(entID)->timers[SpeedUpLoc] = duration;
			break;
		case BallNet:
			///hitta bollen o lägga på en powercompennt förhåven på den.
			BallNetPowerUp(duration);
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
		case BallNetLoc:
			if (GetComponent<PowerUpComponent>(id)->HasPowerUp(BallNet))
			{
				GetComponent<PowerUpComponent>(id)->RemovePowerUp(BallNet);
			}
			break;
	}
}