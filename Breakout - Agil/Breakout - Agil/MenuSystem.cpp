#include "MenuSystem.h"
#include "GameState.h"
#include "EntityManager.h"
#include "ComponentTable.h"
#include "StorageShelf.h"
#include "EventManager.h"
#include "MenyButtonComponent.h"
#include <algorithm>


using namespace std;

MenuSystem::MenuSystem()
{
	mCurrentButton = 0;
	mMinButton = 0;
	mMaxButton = 4;
}

MenuSystem::MenuSystem(string pName) : System(pName)
{
	mCurrentButton = 0;
	mMinButton = 0;
	mMaxButton = 4;
}


MenuSystem::~MenuSystem()
{
}

void MenuSystem::Initialize()
{
	mEventManager = mEventManager->GetInstance();
	mEventManager->Subscribe("Input", this);
	mEventManager->Subscribe("Lost", this);
}

void MenuSystem::Start()
{
}



void MenuSystem::Update(double pDeltaTime)
{
	switch (GameStateClass::GetInstance()->GetGameState())
	{
	case MenuScreen:
		//check input if we're in menu

		break;
	case GameScreen:
		break;
	case DeathScreen:
		break;
	case PauseScreen:
		break;
	default:
		break;
	}


}

void MenuSystem::Pause()
{
}

void MenuSystem::Stop()
{
}

void MenuSystem::OnEvent(Event * pEvent)
{
	if (pEvent->mID == "Input")
	{
		string tKeyPressed = *(string*)pEvent->mPayload["KeyPressed"];
		
		if (tKeyPressed == "UP")
		{
			mCurrentButton--;
			mCurrentButton = max(mCurrentButton, mMinButton);
#ifdef _DEBUG
			cout << "CurrentBottonNum : " << mCurrentButton << endl;
#endif // DEBUG
		}
		else if (tKeyPressed == "DOWN")
		{
			mCurrentButton++;
			mCurrentButton = min(mCurrentButton, mMaxButton);
#ifdef _DEBUG
			cout << "CurrentBottonNum : " << mCurrentButton << endl;
#endif // DEBUG
		}
		else if (tKeyPressed == "PAUSE")
		{
			cout << "----PAUSE----" << endl;//D�placer vers la droite CODE S'IL VOUS PAUSE !
			GameStateClass::GetInstance()->SetGameState(GameState::PauseScreen);
			mCurrentButton = PauseResume;
			mMinButton = PauseResume;
			mMaxButton = PauseQuitToMainMenu;
		}
		else if (tKeyPressed == "UNPAUSE")
		{
			cout << "----UNPAUSE----" << endl;//D�placer vers la droite CODE S'IL VOUS PAUSE !
			GameStateClass::GetInstance()->SetGameState(GameState::GameScreen);
		}
		else if (tKeyPressed == "ENTER")
		{
			////1Start
			////2Quit
			GameStateClass* tGameStateClass = GameStateClass::GetInstance();
			EventManager::Payload tPayload;
			int* tMapID = nullptr;

			switch (mCurrentButton)
			{
			case MainStart:
#ifdef _DEBUG
				cout << "Starting game.." << endl;
#endif // DEBUG
				tGameStateClass->SetGameState(GameScreen);
				tMapID = new int();
				*tMapID = 0;
				tPayload["MapID"] = tMapID;
				EventManager::GetInstance()->BroadcastEvent("GenerateWorld", tPayload);
				break;
			case MainOption:
				break;
			case MainHighscore:
				break;
			case MainTutorial:
				break;
			case MainQuit:
				exit(0);
				break;
			case PauseResume:
#ifdef _DEBUG
				cout << "Resuming game.." << endl;
#endif // DEBUG
				GameStateClass::GetInstance()->SetGameState(GameState::GameScreen);
				break;
			case PauseRestartLevel:
				
				EventManager::GetInstance()->BroadcastEvent("RestartWorld", tPayload);
				GameStateClass::GetInstance()->SetGameState(GameState::GameScreen);
#ifdef _DEBUG
				cout << "Restarting level from pause.." << endl;
#endif // DEBUG
				break;
			case PauseQuitToMainMenu:
#ifdef _DEBUG
				cout << "Quitting to main menu from pause.." << endl;
#endif // DEBUG
				EventManager::GetInstance()->BroadcastEvent("DegenerateWorld", tPayload);
				GameStateClass::GetInstance()->SetGameState(GameState::MenuScreen);
				mCurrentButton = MainStart;
				mMinButton = MainStart;
				mMaxButton = MainQuit;
				break;
			case DeathRestartLevel:
#ifdef _DEBUG
				cout << "Restarting level from deathscreen.." << endl;
#endif // DEBUG
				EventManager::GetInstance()->BroadcastEvent("RestartWorld", tPayload);
				GameStateClass::GetInstance()->SetGameState(GameState::GameScreen);
				break;
			case DeathQuitToMainMenu:
#ifdef _DEBUG
				cout << "Quitting to main menu from deathscreen.." << endl;
#endif // DEBUG
				GameStateClass::GetInstance()->SetGameState(GameState::MenuScreen);
				mCurrentButton = MainStart;
				mMinButton = MainStart;
				mMaxButton = MainQuit;
				break;
			default:
				break;
			}
		}
	}
	else if(pEvent->mID == "Lost")
	{
#ifdef _DEBUG
		cout << "Death screen.." << endl;
#endif // DEBUG
		GameStateClass::GetInstance()->SetGameState(GameState::DeathScreen);
		mCurrentButton = DeathRestartLevel;
		mMinButton = DeathRestartLevel;
		mMaxButton = DeathQuitToMainMenu;
	}
	//change here on input
}
