#include "PhysicSystem.h"
#include "EventManager.h"

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

void PhysicSystem::Update()
{

}

void PhysicSystem::Pause()
{

}

void PhysicSystem::Stop()
{

}

void PhysicSystem::OnEvent(Event* pEvent)
{
	if (pEvent->mID == "DebugTest")
	{
		cout << "Recieved event. Data: ";
		int tData = 0;
		memcpy(&tData, pEvent->mPayload["Debugdata"], 4);
		cout << tData;
	}
}