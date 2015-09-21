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

	mGraphicsInterface = GraphicsInterface::GetSingleton();
	mGraphicsInterface->Initialize();

}

void RenderSystem::Start()
{

}
void RenderSystem::Update(double pDeltaTime)
{
	EntityManager* tEntManager = tEntManager->GetInstance();
	ComponentTable* tCompTable = tCompTable->GetInstance();
	int tMaxEnt = tEntManager->GetLastEntity();
	MeshComponent testMesh;  //teststuffs
	testMesh.mMaterialID = mGraphicsInterface->CreateTexture(L"davai.dds");
	testMesh.mMeshID = mGraphicsInterface->CreateObject("Box");
	TransformComponent testTransform[1];
	testTransform[0].mPosition.x = -2;
	testTransform[0].mPosition.y = 0;
	testTransform[0].mPosition.z = 8;
	testTransform[0].mQuatRotation.x = 0;
	testTransform[0].mQuatRotation.y = 0;
	testTransform[0].mQuatRotation.z = 0;
	testTransform[0].mQuatRotation.w = 0;
	mGraphicsInterface->DrawInstancedObjects(testMesh.mMeshID, testMesh.mMaterialID, testTransform, 1);
	mGraphicsInterface->EndDraw();
	for (int i = 0; i < tMaxEnt; i++)
	{
		short tFlags = MeshType | TransformType;
		if (tCompTable->HasComponent(i, tFlags))
		{ //Teststuff
			TransformComponent* tTrans = GetComponent<TransformComponent>(i);
			MeshComponent* tMesh = GetComponent<MeshComponent>(i);
			tTrans->mPosition.z = 8;
			mGraphicsInterface->DrawInstancedObjects(testMesh.mMeshID, testMesh.mMaterialID, tTrans, 1);
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