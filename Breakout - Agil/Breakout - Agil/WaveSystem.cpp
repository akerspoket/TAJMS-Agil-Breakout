#include "WaveSystem.h"
#include "EntityManager.h"
#include "ComponentTable.h"
#include "TransformComponent.h"
#include "LabelComponent.h"
#include "StorageShelf.h"

WaveSystem::WaveSystem()
{

}

WaveSystem::WaveSystem(string pName) :System(pName)
{

}


WaveSystem::~WaveSystem()
{

}

void WaveSystem::Initialize()
{
	mTimer = 0;
}

void WaveSystem::Start()
{

}

void WaveSystem::Update(double pDeltaTime)
{
	mTimer += pDeltaTime;
	EntityManager* tEntManager = tEntManager->GetInstance();
	ComponentTable* tCompTable = tCompTable->GetInstance();
	int tMaxEnt = tEntManager->GetLastEntity();

	for (int i = 0; i < tMaxEnt; i++)
	{
		if (tCompTable->HasComponent(i, LabelType | TransformType))
		{
			TransformComponent* tTrans = GetComponent<TransformComponent>(i);
			LabelComponent* tLabel = GetComponent<LabelComponent>(i);
			if (tLabel->HasLabel(Waveable))
			{
				tTrans->mPosition.z = 8 + sin(tTrans->mPosition.y + mTimer)/6;
			}
		}
	}
}

void WaveSystem::Pause()
{
}

void WaveSystem::Stop()
{
}

void WaveSystem::OnEvent(Event * pEvent)
{
}
