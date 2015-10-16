#include "EnemySystem.h"
#include "EntityManager.h"
#include "ComponentTable.h"
#include "StorageShelf.h"
#include "LabelComponent.h"
#include "EventManager.h"
#include "PowerUpContainComponent.h"
#include "GameState.h"


EnemySystem::EnemySystem()
{
	mCooldown = 3;
}
EnemySystem::EnemySystem(string pName):System(pName)
{
	mCooldown = 3;
}


EnemySystem::~EnemySystem()
{
}

void EnemySystem::Initialize()
{

	//DEBUG STUFF
	mAviablePowerUps.push_back(Piercing);
	mPowerUpTimes.push_back(5.0f);
	
}

void EnemySystem::Start()
{
}

void EnemySystem::Update(double pDeltaTime)
{
	EntityManager* tEntManager = tEntManager->GetInstance();
	ComponentTable* tCompTable = tCompTable->GetInstance();
	int tMaxEnt = tEntManager->GetLastEntity();
	
	switch (GameStateClass::GetInstance()->GetGameState())
	{
	case MenuScreen:
		
		break;
	case GameScreen:
		mCooldown -= pDeltaTime;

		if (mCooldown < 0)
		{
			vector<EntityID> pGoalBlockIDs;

			//find blocks to random from
			for (int i = 0; i < tMaxEnt; i++)
			{
				//Ensure that relevant components exist

				if (tCompTable->HasComponent(i, LabelType) && GetComponent<LabelComponent>(i)->HasLabel(GoalBlock))
				{
					pGoalBlockIDs.push_back(i);
				}
			}


			if (pGoalBlockIDs.size() > 0)
			{
				//random what ships shootin'
				int random = rand() % 100;
				int shipIDtoShoot = pGoalBlockIDs.size(); // max is everyone

														  //if below 80, we use single ship
				if (random < 60)
				{
					shipIDtoShoot = rand() % pGoalBlockIDs.size();
				}


				for (int i = 0; i < pGoalBlockIDs.size(); i++)
				{
					if ((shipIDtoShoot == i || shipIDtoShoot == pGoalBlockIDs.size()) && mAviablePowerUps.size() > 0)
					{
						//random powerup
						int powerUpIndex = rand() % mAviablePowerUps.size();
						int powerup = mAviablePowerUps[powerUpIndex];

						//shoot
						tCompTable->AddComponent(pGoalBlockIDs[i], PowerUpContainType);
						GetComponent<PowerUpContainComponenet>(pGoalBlockIDs[i])->type = powerup;
						GetComponent<PowerUpContainComponenet>(pGoalBlockIDs[i])->duration = mPowerUpTimes[powerUpIndex];

						EventManager::Payload tPayload;
						EntityID* tID = new EntityID();
						*tID = pGoalBlockIDs[i];
						tPayload["EntityID"] = tID;
						EventManager::GetInstance()->BroadcastEvent("SpawnPowerUp", tPayload);

						//remove component
						GetComponent<PowerUpComponent>(pGoalBlockIDs[i])->RemovePowerUp(powerup);
						tCompTable->RemoveComponent(pGoalBlockIDs[i], PowerUpContainType);

					}
				}

				mCooldown = 3;
			}
		}
		break;
	case DeathScreen:
		
		break;
	case PauseScreen:
		
		break;
	default:
		break;
	}

	

	

	

}

void EnemySystem::Pause()
{
}

void EnemySystem::Stop()
{
}

void EnemySystem::OnEvent(Event * pEvent)
{
}
