#include "PhysicSystem.h"
#include "EventManager.h"
#include "EntityManager.h"
#include "ComponentTable.h"
#include "StorageShelf.h"
#include "PhysicComponent.h"
#include "TransformComponent.h"
#include "VelocityComponent.h"

PhysicSystem::PhysicSystem()
{

}

PhysicSystem::~PhysicSystem()
{

}

void PhysicSystem::Initialize()
{
	mEventManager = mEventManager->GetInstance();
	mEventManager->Subscribe("DebugTest", this);
}

void PhysicSystem::Start()
{

}

void PhysicSystem::Update(double pDeltaTime)
{
	EntityManager* tEntManager = tEntManager->GetInstance();
	ComponentTable* tCompTable = tCompTable->GetInstance();
	int tMaxEnt = tEntManager->GetLastEntity();





	//Update position with velocity
	for (int i = 0; i < tMaxEnt; i++)
	{
		
		//Ensure that relevant components exist
		short tFlags = VelocityType | TransformType;
		if (tCompTable->HasComponent(i, tFlags))
		{
			TransformComponent* tTrans = GetComponent<TransformComponent>(i);
			VelocityComponent* tVel= GetComponent<VelocityComponent>(i);

			tTrans->mPosition[0] += tVel->mDirection[0] + tVel->mSpeed;
			tTrans->mPosition[1] += tVel->mDirection[1] + tVel->mSpeed;
			tTrans->mPosition[2] += tVel->mDirection[2] + tVel->mSpeed;
		}
	}
}

void PhysicSystem::Pause()
{

}

void PhysicSystem::Stop()
{

}

void PhysicSystem::OnEvent(Event* pEvent)
{

}