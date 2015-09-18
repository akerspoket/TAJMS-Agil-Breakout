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

	mGraphicsInterface = new GraphicsInterface();
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
	MeshComponent testMesh;
	testMesh.mMaterialID = mGraphicsInterface->CreateTexture(L"davai.dds");
	testMesh.mMeshID = mGraphicsInterface->CreateObject("Box");
	TransformComponent testTransform[1];
	testTransform[0].mPosition[0] = -2;
	testTransform[0].mPosition[1] = 0;
	testTransform[0].mPosition[2] = 8;
	testTransform[0].mQuatRotation[0] = 0;
	testTransform[0].mQuatRotation[1] = 0;
	testTransform[0].mQuatRotation[2] = 0;
	testTransform[0].mQuatRotation[3] = 0;
	mGraphicsInterface->DrawInstancedObjects(testMesh.mMeshID, testMesh.mMaterialID, testTransform, 1);
	mGraphicsInterface->EndDraw();
	for (int i = 0; i < tMaxEnt; i++)
	{
		short tFlags = MeshType | TransformType;
		if (tCompTable->HasComponent(i, tFlags))
		{
			TransformComponent* tTrans = GetComponent<TransformComponent>(i);
			MeshComponent* tMesh = GetComponent<MeshComponent>(i);
			tTrans->mPosition[2] = 8;
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