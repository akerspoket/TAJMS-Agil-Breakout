#include "RenderSystem.h"
#include "EventManager.h"
#include "StorageShelf.h"
#include "PhysicComponent.h"
#include "EntityManager.h"
#include "ComponentTable.h"
#include "TransformComponent.h"
#include "MeshComponent.h"


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
	EntityManager* tEntManager = tEntManager->GetInstance();
	ComponentTable* tCompTable = tCompTable->GetInstance();
	int tMaxEnt = tEntManager->GetLastEntity();

	
	for (int i = 0; i < tMaxEnt; i++)
	{
		short tFlags = MeshType | TransformType;
		if (tCompTable->HasComponent(i, tFlags))
		{
			TransformComponent* tTrans = GetComponent<TransformComponent>(i);
			MeshComponent* tMesh = GetComponent<MeshComponent>(i);
			//send to graphic
		}
	}
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