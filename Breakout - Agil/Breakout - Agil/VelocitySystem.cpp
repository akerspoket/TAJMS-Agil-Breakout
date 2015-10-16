#include "VelocitySystem.h"

#include "EventManager.h"
#include "EntityManager.h"
#include "ComponentTable.h"
#include "StorageShelf.h"

#include "VelocityComponent.h"
#include "TransformComponent.h"
#include "LabelComponent.h"
#include "PowerUpComponent.h"
#include "GameState.h"

VelocitySystem::VelocitySystem()
{
}


VelocitySystem::~VelocitySystem()
{
}

VelocitySystem::VelocitySystem(string pName):System(pName)
{

}

void VelocitySystem::Initialize()
{

}
void VelocitySystem::Start()
{

}

void VelocitySystem::Update(double pDeltaTime)
{
	EntityManager* tEntManager = tEntManager->GetInstance();
	ComponentTable* tCompTable = tCompTable->GetInstance();
	int tMaxEnt = tEntManager->GetLastEntity();



	switch (GameStateClass::GetInstance()->GetGameState())
	{
	case MenuScreen:
		break;
	case GameScreen:
		//Update position with velocity
		for (int i = 0; i < tMaxEnt; i++)
		{
			if (tCompTable->HasComponent(i, TransformType))
			{
				TransformComponent* tTrans = GetComponent<TransformComponent>(i);
				//Update previous position
				tTrans->mPrevPosition = tTrans->mPosition;

				//Ensure that relevant components exist
				if (tCompTable->HasComponent(i, VelocityType))
				{
					float speedFactor = 1;
					if (ComponentTable::GetInstance()->HasComponent(i, PowerUpType)
						&& GetComponent<PowerUpComponent>(i)->HasPowerUp(SpeedUp))
						speedFactor *= 1.5;
					float slomoSpeedFactor = GetComponent<TransformComponent>(i)->mPosition.y*-1;
					if (ComponentTable::GetInstance()->HasComponent(i, PowerUpType) 
						&& GetComponent<PowerUpComponent>(i)->HasPowerUp(SlowMotion)
						&& GetComponent<TransformComponent>(i)->mPosition.y <= 0
						&& GetComponent<VelocityComponent>(i)->mDirection.y <0)
						speedFactor /= (slomoSpeedFactor*0.2)+1;

					VelocityComponent* tVel = GetComponent<VelocityComponent>(i);
					//Update position with velocity
					tTrans->mPosition += tVel->mDirection* tVel->mSpeed * (float)pDeltaTime * speedFactor;
					if (GetComponent <LabelComponent>(i)->HasLabel(Ball))
					{

					}
				}
			}
		}
		break;
	case DeathScreen:
		break;
	case PauseScreen:
		break;
	default:
		break;
	}

	
}
void VelocitySystem::Pause()
{

}
void VelocitySystem::Stop()
{

}
void VelocitySystem::OnEvent(Event* pEvent)
{

}