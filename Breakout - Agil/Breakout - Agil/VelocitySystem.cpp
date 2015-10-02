#include "VelocitySystem.h"

#include "EventManager.h"
#include "EntityManager.h"
#include "ComponentTable.h"
#include "StorageShelf.h"

#include "VelocityComponent.h"
#include "TransformComponent.h"
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

					VelocityComponent* tVel = GetComponent<VelocityComponent>(i);
					//Update position with velocity
					tTrans->mPosition += tVel->mDirection* tVel->mSpeed * (float)pDeltaTime;

					//Update speed with force if needed (SHOULD PROBABLY NOT BE DONE HERE)
					//if (tCompTable->HasComponent(i, VelocityForceType))
					//{
					//	VelocityForceComponent* tVelForce = GetComponent<VelocityForceComponent>(i);

					//	//update position
					//	if (tVelForce->mType == ForceType::ByValue)
					//	{
					//		//tTrans->mPosition += tVel->mDirection * tVelForce->mAmount * (float)pDeltaTime* (float)pDeltaTime * 0.5f;
					//		tVel->mSpeed += tVelForce->mAmount * (float)pDeltaTime;
					//	}
					//	else if (tVelForce->mType == ForceType::Percentage)
					//	{
					//		tVel->mSpeed *= tVelForce->mAmount * (float)pDeltaTime;
					//		//tTrans->mPosition = tVel->mDirection * tVel->mSpeed * tVelForce->mAmount * (float)pDeltaTime;
					//	}

					//	//update speed
					//	if ((tVel->mSpeed > tVelForce->mEndValue) == tVelForce->mIncrease)
					//	{
					//		tVel->mSpeed = tVelForce->mEndValue;
					//		tCompTable->RemoveComponent(i, VelocityForceType);
					//	}

					//}

					//DEBUG
					//if (GetComponent<LabelComponent>(i)->mLabel == Label::Ball)
					//	cout << "Position for pad is: " << tTrans->mPosition.x << " " << tTrans->mPosition.y << endl;

					//END DEBUG
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