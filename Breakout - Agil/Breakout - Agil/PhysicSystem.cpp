#include "PhysicSystem.h"
#include "EventManager.h"
#include "EntityManager.h"
#include "ComponentTable.h"
#include "StorageShelf.h"
#include "PhysicComponent.h"

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

	for (int i = 0; i < tMaxEnt; i++)
	{
		if (tCompTable->HasComponent(i, ComponentType::PhysicType))
		{
			PhysicComponent* tPhys = GetComponent<PhysicComponent>(i);
			tPhys->mIsSphere = !tPhys->mIsSphere;
			cout << tPhys->mIsSphere << endl;
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
	//if (pEvent->mID == "DebugTest")
	//{
	//	cout << "Recieved event. Data: ";
	//	int tData = 0;
	//	memcpy(&tData, pEvent->mPayload["Debugdata"], 4);
	//	cout << tData;
	//}
}