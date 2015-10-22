#include "RenderSystem.h"
#include "EventManager.h"
#include "StorageShelf.h"
#include "PhysicComponent.h"
#include "EntityManager.h"
#include "ComponentTable.h"
#include "TransformComponent.h"
#include "MeshComponent.h"
#include "GameState.h"
#include "LabelComponent.h"
#include "EmitterComponent.h"
#include "VelocityComponent.h"

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
	mEventManager->Subscribe("Collision", this);



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
			if (tCompTable->HasComponent(i, EmitterType))
			{
				EmitterComponent* tEmitter = GetComponent<EmitterComponent>(i);
				for (size_t i = 0; i < MAX_PARTICLE_EMITTER; i++)
				{
					tEmitter->Timers[i] -= pDeltaTime;
					if (tEmitter->Timers[i] < 0)
					{
						tEmitter->EmitterID[i] = -1;
						tEmitter->Timers[i] = 0;
					}
				}

				if (tCompTable->HasComponent(i, TransformType))
				{
					for (size_t k = 0; k < MAX_PARTICLE_EMITTER; k++)
					{

						if (tEmitter->Attached[k] && tEmitter->EmitterID[k] != -1)
						{
							vec3 tVel = vec3(0, 0, 0);
							if (tCompTable->HasComponent(i, VelocityType))
							{
								tVel = GetComponent<VelocityComponent>(i)->mDirection;
							}
							vec3 tPos = GetComponent<TransformComponent>(i)->mPosition;
							mGraphicsInterface->UpdateEmitterPos(GetComponent<EmitterComponent>(i)->EmitterID[k], tPos, tVel);
						}
					}
				}
			}
		}
	
	mGraphicsInterface->DrawThisText(to_string(mScore), vec2(0,800-25),25,mTempTextId);
	mGraphicsInterface->DrawThisText(to_string(mLifes), vec2(775, 800 - 25), 25, mLifeTextID);
	mGraphicsInterface->DrawParticles();
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
	if (pEvent->mID == "Collision")
	{
		EntityID entID1 = *(EntityID*)pEvent->mPayload["ID1"];
		if (GetComponent<LabelComponent>(entID1)->HasLabel(Box))
		{
			vec3 tPos = GetComponent<TransformComponent>(entID1)->mPosition;
			tPos.z -= 1;
			mGraphicsInterface->CreateParticleEmitter(tPos, vec3(1.0f, 1.0f, 0.0f), 0.05f, 5,vec3(0,0,0), 0.2f, 1.0f, 0, 0.7f,3);
		}
		EntityID entID2 = *(EntityID*)pEvent->mPayload["ID2"];
		if (GetComponent<LabelComponent>(entID2)->HasLabel(Box))
		{
			vec3 tPos = GetComponent<TransformComponent>(entID2)->mPosition;
			tPos.z -= 1;
			mGraphicsInterface->CreateParticleEmitter(tPos, vec3(1.0f, 1.0f, 0.0f), 0.05f, 5,vec3(0,0,0), 0.2f, 1.0f, 0, 0.7f,3);
		}
	}

	if (pEvent->mID == "DrawLife")
	{
		mLifes = *(int*)pEvent->mPayload["life"];
	}
}