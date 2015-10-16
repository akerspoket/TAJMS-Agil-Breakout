#include "RenderSystem.h"
#include "EventManager.h"
#include "StorageShelf.h"
#include "PhysicComponent.h"
#include "EntityManager.h"
#include "ComponentTable.h"
#include "TransformComponent.h"
#include "MeshComponent.h"
#include "GameState.h"


RenderSystem::RenderSystem()
{
	mLifes = 0;
}

RenderSystem::RenderSystem(string pName):System(pName)
{
	mLifes = 0;
}


RenderSystem::~RenderSystem()
{
}

void RenderSystem::Initialize()
{
	mEventManager = mEventManager->GetInstance();
	mEventManager->Subscribe("DebugTest", this);
	mEventManager->Subscribe("DrawScore", this);
	mEventManager->Subscribe("DrawLife", this);



}
void RenderSystem::Initialize(SDL_Window* pWin)
{
	mGraphicsInterface = GraphicsInterface::GetSingleton();
	mGraphicsInterface->Initialize(90.0f, 600.0f, 800.0f, 0.1f, 100, -4.0f, pWin);
	mTempTextId = mGraphicsInterface->CreateText(60);
	mLifeTextID = mGraphicsInterface->CreateText(5);
}


void RenderSystem::Start()
{

}
void RenderSystem::Update(double pDeltaTime)
{
	EntityManager* tEntManager = tEntManager->GetInstance();
	ComponentTable* tCompTable = tCompTable->GetInstance();
	int tMaxEnt = tEntManager->GetLastEntity();

	short tFlags = 0;
	switch (GameStateClass::GetInstance()->GetGameState())
	{
	case MenuScreen:
		tFlags = MeshType | TransformType;
	break;
	case GameScreen:
		tFlags = MeshType | TransformType;
	break;
	case DeathScreen:
		tFlags = MeshType | TransformType;
	break;
	case PauseScreen:
		tFlags = MeshType | TransformType;
	break;
	default:
	break;
	}

		for (int i = 0; i < tMaxEnt; i++)
		{
		
			if (tCompTable->HasComponent(i, tFlags))
			{ //Teststuff
				TransformComponent* tTrans = GetComponent<TransformComponent>(i);
				MeshComponent* tMesh = GetComponent<MeshComponent>(i);
				TransformComponent tTransFix = *tTrans;

				mGraphicsInterface->DrawInstancedObjects(tMesh->mMeshID, tMesh->mMaterialID, &tTransFix, 1); 
			}
		}
	
	mGraphicsInterface->DrawThisText(to_string(mScore), vec2(0,800-25),25,mTempTextId);
	mGraphicsInterface->DrawThisText(to_string(mLifes), vec2(775, 800 - 25), 25, mLifeTextID);
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

	if (pEvent->mID == "DrawScore")
	{
		mScore = *(int*)pEvent->mPayload["score"];
	}
	if (pEvent->mID == "DrawLife")
	{
		mLifes = *(int*)pEvent->mPayload["life"];
	}
}