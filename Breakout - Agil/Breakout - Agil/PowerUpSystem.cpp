#include "PowerUpSystem.h"
#include "EventManager.h"
#include "EntityManager.h"
#include "ComponentTable.h"
#include "StorageShelf.h"
#include "VelocityComponent.h"
#include "PowerUpComponent.h"
#include "PowerUpContainComponent.h"
#include "LabelComponent.h"
#include "TransformComponent.h"
#include "EntityFactory.h"
#include "MeshComponent.h"
#include "GraphicsInterface.h"

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
	EventManager::GetInstance()->Subscribe("SpawnPowerUp", this);
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
void PowerUpSystem::ApplySpeedPowerUp (float pTime)
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
				tCompTable->AddComponent(i, PowerUpType);
				GetComponent<PowerUpComponent>(i)->timers[SpeedUpLoc] = pTime;
				GetComponent<PowerUpComponent>(i)->AddPowerUp(SpeedUp);
			}
		}
	}
}
void PowerUpSystem::ApplyBallNetPowerUp(float pTime)
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
				tCompTable->AddComponent(i, PowerUpType);
				GetComponent<PowerUpComponent>(i)->timers[BallNetLoc] = pTime;
				GetComponent<PowerUpComponent>(i)->AddPowerUp(BallNet);
			}
		}
	}

	//test


}
void PowerUpSystem::ApplyPiercingPowerUp(float pTime)
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
				tCompTable->AddComponent(i, PowerUpType);
				GetComponent<PowerUpComponent>(i)->timers[PiercingLoc] = pTime;
				GetComponent<PowerUpComponent>(i)->AddPowerUp(Piercing);
			}
		}
	}

	//test

}
void PowerUpSystem::ApplyMagnetPowerUp(float pTime)
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
				tCompTable->AddComponent(i, PowerUpType);
				GetComponent<PowerUpComponent>(i)->timers[MagnetPUpLoc] = pTime;
				GetComponent<PowerUpComponent>(i)->AddPowerUp(MagnetPUp);
			}
		}
	}
}

void PowerUpSystem::ApplyInvertPowerDown(float pTime)
{
	EntityManager* tEntManager = tEntManager->GetInstance();
	ComponentTable* tCompTable = tCompTable->GetInstance();
	int tMaxEnt = tEntManager->GetLastEntity();

	for (size_t i = 0; i < tMaxEnt; i++)
	{
		if (tCompTable->HasComponent(i, LabelType))
		{
			if (GetComponent<LabelComponent>(i)->HasLabel(Pad))
			{
				tCompTable->AddComponent(i, PowerUpType);
				GetComponent<PowerUpComponent>(i)->timers[InvertDownLoc] = pTime;
				GetComponent<PowerUpComponent>(i)->AddPowerUp(InvertDown);
			}
		}
	}
}

void PowerUpSystem::ApplySlowMotionPowerUp(float pTime)
{
	EntityManager* tEntManager = tEntManager->GetInstance();
	ComponentTable* tCompTable = tCompTable->GetInstance();
	int tMaxEnt = tEntManager->GetLastEntity();

	for (size_t i = 0; i < tMaxEnt; i++)
	{
		if (tCompTable->HasComponent(i, LabelType | VelocityType))
		{
			if (GetComponent<LabelComponent>(i)->HasLabel(Ball))
			{
				tCompTable->AddComponent(i, PowerUpType);
				GetComponent<PowerUpComponent>(i)->timers[SlowMotionLoc] = pTime;
				GetComponent<PowerUpComponent>(i)->AddPowerUp(SlowMotion);
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
		EntityID pupID = *(EntityID*)pEvent->mPayload["PupEntityID"];

		PowerUpContainComponenet* pupContain = GetComponent<PowerUpContainComponenet>(pupID);


		short mask = pupContain->type;
		float duration = pupContain->duration;

		//need to zero the memory 
		if (!tCompTable->HasComponent(entID, PowerUpType))
		{
			*GetComponent<PowerUpComponent>(entID) = PowerUpComponent();
		}
		//tCompTable->AddComponent(entID, PowerUpType);

		switch (mask)
		{
		case SpeedUp:
			ApplySpeedPowerUp(duration);
			break;
		case BallNet:
			///hitta bollen o l�gga p� en powercompennt f�rh�ven p� den.
			ApplyBallNetPowerUp(duration);
			break;
		case Piercing:
			ApplyPiercingPowerUp(duration);
			break;
		case MagnetPUp:
			ApplyMagnetPowerUp(duration);
			break;
		case InvertDown:
			ApplyInvertPowerDown(duration);
			break;
		case SlowMotion:
			ApplySlowMotionPowerUp(duration);
			break;
		}
	}

	if (pEvent->mID == "SpawnPowerUp")
	{
		EntityID entID = *(EntityID*)pEvent->mPayload["EntityID"];
		if (ComponentTable::GetInstance()->HasComponent(entID, PowerUpContainType)) //Better safe than sorry..
		{
			PowerUpContainComponenet* tPupContain = GetComponent<PowerUpContainComponenet>(entID);
			EntityID tNewID = EntityFactory::GetInstance()->CreateEntity("DEBUGPUP");
			GetComponent<PowerUpContainComponenet>(tNewID)->duration = tPupContain->duration;
			GetComponent<PowerUpContainComponenet>(tNewID)->type = tPupContain->type;
			GetComponent<TransformComponent>(tNewID)->mPosition = GetComponent<TransformComponent>(entID)->mPosition;
			switch (tPupContain->type)
			{
			case SpeedUp:
				GetComponent<MeshComponent>(tNewID)->mMaterialID = GraphicsInterface::GetSingleton()->CreateTexture("Textures/PupSpeedUp");
				break;
			case BallNet:
				GetComponent<MeshComponent>(tNewID)->mMaterialID = GraphicsInterface::GetSingleton()->CreateTexture("Textures/PupBallNet");
				break;
			case Piercing:
				GetComponent<MeshComponent>(tNewID)->mMaterialID = GraphicsInterface::GetSingleton()->CreateTexture("Textures/PupPiercing");
				break;
			case MagnetPUp:
				GetComponent<MeshComponent>(tNewID)->mMaterialID = GraphicsInterface::GetSingleton()->CreateTexture("Textures/PupMagnet");
				break;
			case SlowMotion:
				GetComponent<MeshComponent>(tNewID)->mMaterialID = GraphicsInterface::GetSingleton()->CreateTexture("Textures/PupSlomo");
				break;
			}
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
	case InvertDownLoc:
		if (GetComponent<PowerUpComponent>(id)->HasPowerUp(InvertDown))
		{
			GetComponent<PowerUpComponent>(id)->RemovePowerUp(InvertDown);
		}
		break;
	case SlowMotionLoc:
		if (GetComponent<PowerUpComponent>(id)->HasPowerUp(SlowMotion))
		{
			GetComponent<PowerUpComponent>(id)->RemovePowerUp(SlowMotion);
		}
		break;
	}
}