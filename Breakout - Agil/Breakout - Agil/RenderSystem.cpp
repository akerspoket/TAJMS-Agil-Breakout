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
	mGraphicsInterface->Initialize(45.0f, 800.0f, 600.0f, 0.1f, 100, 0.0f);

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
	testMesh.mMaterialID = mGraphicsInterface->CreateTexture(L"bthcolor.dds");
	testMesh.mMeshID = mGraphicsInterface->CreateObject("BTH");
	//TransformComponent testTransform[1];
	//testTransform[0].mPosition.x = -2;
	//testTransform[0].mPosition.y = 0;
	//testTransform[0].mPosition.z = 8;
	//testTransform[0].mQuatRotation.x = 0;
	//testTransform[0].mQuatRotation.y = 0;
	//testTransform[0].mQuatRotation.z = 0;
	//testTransform[0].mQuatRotation.w = 0;
	//mGraphicsInterface->DrawInstancedObjects(testMesh.mMeshID, testMesh.mMaterialID, testTransform, 1);
	//mGraphicsInterface->EndDraw();
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