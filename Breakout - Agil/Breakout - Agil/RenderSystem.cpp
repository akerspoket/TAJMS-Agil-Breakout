#include "RenderSystem.h"
#include "EventManager.h"
#include "StorageShelf.h"
#include "PhysicComponent.h"



RenderSystem::RenderSystem()
{
}


RenderSystem::~RenderSystem()
{
}

void RenderSystem::Initialize()
{
	mEventManager = mEventManager->GetInstance();
	mEventManager->Subscribe("DebugTest", this);


	
}

void RenderSystem::Start()
{

}
void RenderSystem::Update(double pDeltaTime)
{
	//PhysicComponent* comp = GetComponent<PhysicComponent>(23);
}
void RenderSystem::Pause()
{

}
void RenderSystem::Stop()
{

}
void RenderSystem::OnEvent(Event* pEvent)
{

}