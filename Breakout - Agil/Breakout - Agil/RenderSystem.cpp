#include "RenderSystem.h"
#include "EventManager.h"


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