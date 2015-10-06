#include "TriggerSystem.h"
#include "EventManager.h"
#include "LevelManager.h"
#include "EntityManager.h"
#include "ComponentTable.h"
#include "LabelComponent.h"
#include "VelocityComponent.h"
#include "StorageShelf.h"
#include "GameState.h"
#include "MenyButtonComponent.h"



TriggerSystem::TriggerSystem()
{
	mCreateNextLevel = true;
	mDegenerateWorld = false;
	mCurrentLevel = -1;
}

TriggerSystem::TriggerSystem(string pName):System(pName)
{
	mCreateNextLevel = true;
	mDegenerateWorld = false;
	mCurrentLevel = -1;
}


TriggerSystem::~TriggerSystem()
{
}

void TriggerSystem::Initialize()
{
	mEventManager = mEventManager->GetInstance();
	mEventManager->Subscribe("CollideWithBottom", this);
	mEventManager->Subscribe("CollideWithGoalBlock", this);
	mEventManager->Subscribe("DegenerateWorld", this);
	mEventManager->Subscribe("RestartWorld", this);
	mEventManager->Subscribe("LaunchButtonPressed", this);
	mEventManager->Subscribe("GenerateWorld", this);
	mEventManager->Subscribe("DegeneratePauseMenu", this);
	mEventManager->Subscribe("GenerateMenu", this);

	LevelManager* tLevelManager = tLevelManager->GetInstance();
	tLevelManager->Initialize();
	//LevelManager* tLevelManager = tLevelManager->GetInstance();
	//tLevelManager->GenerateWorld("Levels/Level1.txt");
	tLevelManager->GenerateMainMenu();

	//add levels here
	mMapNames.push_back("Levels/Level1.txt");
	mMapNames.push_back("Levels/Level2.txt");
}

void TriggerSystem::Start()
{

}

void TriggerSystem::Update(double pDeltaTime)
{
	EntityManager* tEntMan = tEntMan->GetInstance();
	ComponentTable* tCompTable = tCompTable->GetInstance();
	int tMaxEnt = tEntMan->GetLastEntity();

	//degenerate world, can be set from events incomming
	if (mDegenerateWorld)
	{
		LevelManager::GetInstance()->DegenerateEverything();
		mDegenerateWorld = false;
	}
	if (mGenerateMenu)
	{

		switch ((mGenerateMenu - 1))
		{
		case MainMenu:
			LevelManager::GetInstance()->GenerateMainMenu();
			break;
		case PauseMenu:
			LevelManager::GetInstance()->GeneratePauseScreen();
			break;
		case DeathMenu:
			LevelManager::GetInstance()->GenerateDeathScreen();
			break;
		default:
			break;
		}
		mGenerateMenu = 0;
	}

	switch (GameStateClass::GetInstance()->GetGameState())
	{
	case MenuScreen:

		break;
	case GameScreen:
		if (mCreateNextLevel)
		{
			mCurrentLevel++;
			//if we have enough maps
			if (mMapNames.size() - 1 >= mCurrentLevel)
			{
				LevelManager::GetInstance()->GenerateWorld(mMapNames[mCurrentLevel]);
			}
			mCreateNextLevel = false;
		}

		mNumOfBallsActive = 0;
		mNumOfGoalBlocksActive = 0;

		//check how many balls we have active and goals cause why not
		for (int i = 0; i < tMaxEnt; i++)
		{
			if (tCompTable->HasComponent(i, LabelType))
			{
				Label tLabel = GetComponent<LabelComponent>(i)->mLabel;

				if (tLabel == Label::Ball)
				{
					mNumOfBallsActive++;
				}
				else if (tLabel == Label::GoalBlock)
				{
					mNumOfGoalBlocksActive++;
				}
			}
		}

		//if no goal blocks, we go to next map, even if we can do this by event, we might explode or something that doesn't trigger, not sure how we want it
#ifdef _DEBUG
		if (mNumOfGoalBlocksActive == 0 && mNumOfBallsActive != 0)
		{
			//DEBUG

			cout << "WARNING - MAP HAS NO GOAL LEFT, EITHER WRONG IN MAP OR SOME REALLY WIERD BUG" << endl;

			//END DEBUG
		}
#endif

		break;
	case DeathScreen:
		break;
	case PauseScreen:
		break;
	default:
		break;
	}
}

void TriggerSystem::Pause()
{

}

void TriggerSystem::Stop()
{

}

void TriggerSystem::OnEvent(Event* pEvent)
{
	EntityManager* tEntMan = tEntMan->GetInstance();
	ComponentTable* tCompTable = tCompTable->GetInstance();

	int tMaxEnt = tEntMan->GetLastEntity();

	string pEventID = pEvent->mID;

	if (pEventID == "CollideWithBottom")
	{
		mNumOfBallsActive--;

		//no balls active
		if (mNumOfBallsActive < 1)
		{
			mDegenerateWorld = true;
			EventManager::Payload tPayload;
			EventManager::GetInstance()->BroadcastEvent("Lost", tPayload);

			//DEBUG
#ifdef _DEBUG
			cout << "You lost" << endl;
#endif
			//END DEBUG
		}
	}
	else if (pEventID == "CollideWithGoalBlock")
	{
		mNumOfGoalBlocksActive--;
		if (mNumOfGoalBlocksActive < 1)
		{
			mCreateNextLevel = true;
			mDegenerateWorld = true;

			//DEBUG
#ifdef _DEBUG
			cout << "You won the level, loading next!" << endl;
#endif
			//END DEBUG
		}
	}

	else if (pEventID == "LaunchButtonPressed")
	{
		for (int i = 0; i < tMaxEnt; i++)
		{
			short pMask = AttachedType | LabelType;
			if (tCompTable->HasComponent(i, pMask) && GetComponent<LabelComponent>(i)->mLabel == Label::Ball)
			{
				tCompTable->RemoveComponent(i, AttachedType);
				tCompTable->AddComponent(i, VelocityType);
				GetComponent<VelocityComponent>(i)->mDirection = vec3(1, 1, 0).Normalize();
				GetComponent<VelocityComponent>(i)->mSpeed = 12;
			}
		}
	}

	else if (pEventID == "DegenerateWorld")
	{
		mDegenerateWorld = true;
	}

	else if (pEventID == "GenerateWorld")
	{
		int mapID = *(int*)pEvent->mPayload["MapID"];
		mCurrentLevel = mapID - 1;
		mCreateNextLevel = true;
	}

	else if (pEventID == "RestartWorld")
	{
		mDegenerateWorld = true;
		mCreateNextLevel = true;
		mCurrentLevel--;
	}

	else if (pEventID == "DegeneratePauseMenu")
	{
		LevelManager::GetInstance()->DegenerateMenu();
	}
	else if (pEventID  == "GenerateMenu")
	{
		int tMenuID = *(int*)pEvent->mPayload["MenuID"];

		//set next menu to be loaded, but do + 1 for bool check on 0
		switch (tMenuID)
		{
		case MainMenu:
			mGenerateMenu = MainMenu + 1;
			break;
		case PauseMenu:
			mGenerateMenu = PauseMenu + 1;
			break;
		case DeathMenu:
			mGenerateMenu = DeathMenu + 1;
			break;
		default:
			break;
		}
	
	}
}