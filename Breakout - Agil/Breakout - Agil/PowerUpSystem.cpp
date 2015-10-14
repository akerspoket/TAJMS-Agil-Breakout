#include "PowerUpSystem.h"
#include "EventManager.h"
#include "EntityManager.h"
#include "ComponentTable.h"
#include "StorageShelf.h"
#include "VelocityComponent.h"
#include "PowerUpComponent.h"
#include "LabelComponent.h"
#include "TransformComponent.h"

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

void PowerUpSystem::MagnetPowerUp(EntityID pPadID, EntityID pPowerUpID)
{
	TransformComponent* tPadTrans = GetComponent<TransformComponent>(pPadID);
	TransformComponent* tPowerUpTrans = GetComponent<TransformComponent>(pPowerUpID);
	VelocityComponent* tPowerUpVelocity = GetComponent<VelocityComponent>(pPowerUpID);

	float tDirection = tPadTrans->mPosition.x - tPowerUpTrans->mPosition.x;

	if (tDirection != 0)
	{
		tDirection /= abs(tDirection);

		tPowerUpVelocity->mDirection = vec3(tPowerUpVelocity->mDirection + vec3(tDirection * 0.01f, 0, 0));
		tPowerUpVelocity->mDirection;
	}
}

void PowerUpSystem::Update(double pDeltaTime)
{
	EntityManager* tEntManager = tEntManager->GetInstance();
	ComponentTable* tCompTable = tCompTable->GetInstance();
	int tMaxEnt = tEntManager->GetLastEntity();

	EntityID tPadID = -1;
	EntityID tPowerUpID = -1;

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

			if (tPup->HasPowerUp(MagnetPUp))
			{
				tPowerUpID = i;
			}
			
		}
		if (tCompTable->HasComponent(i, LabelType | TransformType))
		{
			if (GetComponent<LabelComponent>(i)->HasLabel(Pad))
			{
				tPadID = i;
			}
		}

	}
	if (tPadID != -1 && tPowerUpID != -1)
	{
		MagnetPowerUp(tPadID, tPowerUpID);
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
			if (GetComponent<LabelComponent>(i)->HasLabel(Ball))
			{
				GetComponent<PowerUpComponent>(i)->timers[BallNetLoc] = pTime;
			}
		}
	}

	//test
	

}
void PowerUpSystem::PiercingPowerUp(float pTime)
{
	EntityManager* tEntManager = tEntManager->GetInstance();
	ComponentTable* tCompTable = tCompTable->GetInstance();
	int tMaxEnt = tEntManager->GetLastEntity();

	for (size_t i = 0; i < tMaxEnt; i++)
	{
		if (tCompTable->HasComponent(i, LabelType))
		{
			if (GetComponent<LabelComponent>(i)->HasLabel(Ball))
			{
				GetComponent<PowerUpComponent>(i)->timers[PiercingLoc] = pTime;
			}
		}
	}

	//test

}
void PowerUpSystem::MagnetPowerUp(float pTime)
{
	EntityManager* tEntManager = tEntManager->GetInstance();
	ComponentTable* tCompTable = tCompTable->GetInstance();
	int tMaxEnt = tEntManager->GetLastEntity();

	for (size_t i = 0; i < tMaxEnt; i++)
	{
		if (tCompTable->HasComponent(i, LabelType))
		{
			if (GetComponent<LabelComponent>(i)->HasLabel(Ball))
			{
				GetComponent<PowerUpComponent>(i)->timers[MagnetPUpLoc] = pTime;
			}
		}
	}
}
void PowerUpSystem::OnEvent(Event* pEvent)
{
	EntityManager* tEntMan = tEntMan->GetInstance();
	ComponentTable* tCompTable = tCompTable->GetInstance();

	if (pEvent->mID == "PowerUpPickedUp")
	{
		EntityID entID = *(EntityID*)pEvent->mPayload["EntityID"];
		short mask = *(short*)pEvent->mPayload["mask"];
  		float duration = *(float*)pEvent->mPayload["duration"];

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
		case Piercing:
			PiercingPowerUp(duration);
			break;
		case MagnetPUp:
			MagnetPowerUp(duration);
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
		case PiercingLoc:
			if (GetComponent<PowerUpComponent>(id)->HasPowerUp(Piercing))
			{
				GetComponent<PowerUpComponent>(id)->RemovePowerUp(Piercing);
			}
			break;
		case MagnetPUpLoc:
			if (GetComponent<PowerUpComponent>(id)->HasPowerUp(MagnetPUp))
			{
				GetComponent<PowerUpComponent>(id)->RemovePowerUp(MagnetPUp);
			}
			break;
	}
}