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

RenderSystem::RenderSystem(string pName):System(pName)
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
void RenderSystem::Initialize(SDL_Window* pWin)
{
	mGraphicsInterface = GraphicsInterface::GetSingleton();
	mGraphicsInterface->Initialize(45.0f, 600.0f, 800.0f, 0.1f, 100, -13.0f, pWin);
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
		{ //Teststuff
			TransformComponent* tTrans = GetComponent<TransformComponent>(i);
			MeshComponent* tMesh = GetComponent<MeshComponent>(i);
			tTrans->mPosition.z = 8;
			//mGraphicsInterface->DrawInstancedObjects(testMesh.mMeshID, testMesh.mMaterialID, tTrans, 1);
			mGraphicsInterface->DrawInstancedObjects(tMesh->mMeshID, tMesh->mMaterialID, tTrans, 1);
		}
	}
	mGraphicsInterface->EndDraw();
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