#include "InputSystem.h"
#include "EventManager.h"
#include "StorageShelf.h"
#include "LabelComponent.h"
#include "VelocityComponent.h"
#include "ComponentTable.h"
#include "UserCmdStruct.h"
#include "GameState.h"

using namespace std;

InputSystem::InputSystem()
{
}

InputSystem::InputSystem(string pName):System(pName)
{
}


InputSystem::~InputSystem()
{
}

void InputSystem::Initialize()
{
	mEventManager = mEventManager->GetInstance();
	//mEventManager->Subscribe("DebugTest", this);
}

void InputSystem::Start()
{

}
void InputSystem::CheckKeyboard()
{
	
	gUserCmd.mKeysPressed.clear();
	if (mKeyState[SDL_SCANCODE_LEFT])
	{
		gUserCmd.mLeftArrowPressed = true;
	}
	else
	{
		gUserCmd.mLeftArrowPressed = false;
	}
	if (mKeyState[SDL_SCANCODE_RIGHT])
	{
		gUserCmd.mRightArrowPressed = true;
	}
	else
	{
		gUserCmd.mRightArrowPressed = false;
	}
	if (mKeyState[SDL_SCANCODE_UP])
	{
		gUserCmd.mUpArrowPressed = true;
	}
	else
	{
		gUserCmd.mUpArrowPressed = false;
	}
	if (mKeyState[SDL_SCANCODE_DOWN])
	{
		gUserCmd.mDownArrowPressed = true;
	}
	else
	{
		gUserCmd.mDownArrowPressed = false;
	}
	if (mKeyState[SDL_SCANCODE_A])
	{
		gUserCmd.mKeysPressed.push_back('a');
	}
	if (mKeyState[SDL_SCANCODE_D])
	{
		gUserCmd.mKeysPressed.push_back('d');
	}
	if (mKeyState[SDL_SCANCODE_P])
	{
		gUserCmd.mKeysPressed.push_back('p');
	}
	if (mKeyState[SDL_SCANCODE_W])
	{
		gUserCmd.mKeysPressed.push_back('w');
	}
	if (mKeyState[SDL_SCANCODE_S])
	{
		gUserCmd.mKeysPressed.push_back('s');
	}
	if (mKeyState[SDL_SCANCODE_X])
	{
		gUserCmd.mKeysPressed.push_back('x'); //sEXy debug button
	}
	if (mKeyState[SDL_SCANCODE_ESCAPE])
	{
		cout << "Stäng av programmet";
		exit(0);
	}
	if (mKeyState[SDL_SCANCODE_SPACE])
	{
		gUserCmd.mSpaceButtonPressed = true;
	}
	else
	{
		gUserCmd.mSpaceButtonPressed = false;
	}
	if(mKeyState[SDL_SCANCODE_RETURN])
	{
		gUserCmd.mEnterButtonPressed = true;
	}
	else
	{
		gUserCmd.mEnterButtonPressed = false;
	}
}
void EnterPressCheck()
{
	////Enterpressing
	if (gUserCmd.mEnterButtonPressed && !gLastUserCmd.mEnterButtonPressed)
	{
		EventManager::Payload tPayload;
		string* tString = new string();
		*tString = "ENTER";
		tPayload["KeyPressed"] = tString;
		EventManager::GetInstance()->BroadcastEvent("Input", tPayload);
	}
}

void UpDownPressCheck()
{
	int tVectorInput = gUserCmd.mKeysPressed.size();
	int tVectorLastInput = gLastUserCmd.mKeysPressed.size();

	bool moveUp = gUserCmd.mUpArrowPressed && !gLastUserCmd.mUpArrowPressed;
	bool moveDown = gUserCmd.mDownArrowPressed && !gLastUserCmd.mDownArrowPressed;



	for (size_t i = 0; i < tVectorInput; i++)
	{
		bool t_Found = false;
		for (size_t k = 0; k < tVectorLastInput; k++)
		{
			if (gUserCmd.mKeysPressed[i] == gLastUserCmd.mKeysPressed[k])
			{
				t_Found = true;
				k = tVectorLastInput;
			}
		}
		if (!t_Found)
		{
			if (gUserCmd.mKeysPressed[i] == 'w')
			{
				moveUp = true;
			}
			else if (gUserCmd.mKeysPressed[i] == 's')
			{
				moveDown = true;
			}
		}
	}

	if (moveUp && !moveDown)
	{
		EventManager::Payload tPayload;
		string* tString = new string();
		*tString = "UP";
		tPayload["KeyPressed"] = tString;
		EventManager::GetInstance()->BroadcastEvent("Input", tPayload);
	}
	else if (moveDown && !moveUp)
	{
		EventManager::Payload tPayload;
		string* tString = new string();
		*tString = "DOWN";
		tPayload["KeyPressed"] = tString;
		EventManager::GetInstance()->BroadcastEvent("Input", tPayload);
	}
}

void InputSystem::MoveRight(EntityID pEntityID)
{
	ComponentTable* tCompTable = tCompTable->GetInstance();

	tCompTable->AddComponent(pEntityID, ComponentType::VelocityType);

	VelocityComponent* tVel = GetComponent<VelocityComponent>(pEntityID);
	tVel->mDirection = vec3(1.0f, 0.0f, 0.0f);
}

void InputSystem::MoveLeft(EntityID pEntityID)
{
	ComponentTable* tCompTable = tCompTable->GetInstance();
	
	tCompTable->AddComponent(pEntityID, ComponentType::VelocityType);
	
	VelocityComponent* tVel = GetComponent<VelocityComponent>(pEntityID);
	tVel->mDirection = vec3(-1.0f, 0.0f, 0.0f);
}

void InputSystem::StandStill(EntityID pEntityID)
{
	ComponentTable* tCompTable = tCompTable->GetInstance();

	tCompTable->AddComponent(pEntityID, ComponentType::VelocityType);

	VelocityComponent* tVel = GetComponent<VelocityComponent>(pEntityID);
	tVel->mDirection = vec3(0.0f, 0.0f, 0.0f);
}

void InputSystem::PadInput(EntityID pEntityID)
{
	int tVectorInput = gUserCmd.mKeysPressed.size();
	int tVectorLastInput = gLastUserCmd.mKeysPressed.size();

	bool moveLeft = gUserCmd.mLeftArrowPressed;
	bool moveRight = gUserCmd.mRightArrowPressed;

	if (gUserCmd.mSpaceButtonPressed)
	{
		std::unordered_map<string, void*> tPayLoad; //Sending empty payload has to be fixed...
		EventManager::GetInstance()->BroadcastEvent("LaunchButtonPressed", tPayLoad);
	}

	for (size_t i = 0; i < tVectorInput; i++)
	{
		if (gUserCmd.mKeysPressed[i] == 'a')
		{
			moveLeft = true;
		}
		if (gUserCmd.mKeysPressed[i] == 'd')
		{
			moveRight = true;
		}
	}

	if (moveLeft == moveRight )
	{
		StandStill(pEntityID);
	}
	else if (moveLeft)
	{
		MoveLeft(pEntityID);
	}
	else if (moveRight)
	{
		MoveRight(pEntityID);
	}
	
	
	
}

void InputSystem::GameInput()
{
	int tVectorInput = gUserCmd.mKeysPressed.size();
	int tVectorLastInput = gLastUserCmd.mKeysPressed.size();
	for (size_t i = 0; i < tVectorInput; i++)
	{
		bool t_Found = false;
		for (size_t k = 0; k < tVectorLastInput; k++)
		{
			if (gUserCmd.mKeysPressed[i] == gLastUserCmd.mKeysPressed[k])
			{
				t_Found = true;
				k = tVectorLastInput;
			}
		}
		if (!t_Found)
		{
			if (gUserCmd.mKeysPressed[i] == 'p')
			{
				EventManager::Payload tPayload;
				string* tString = new string();
				*tString = "PAUSE";
				tPayload["KeyPressed"] = tString;
				EventManager::GetInstance()->BroadcastEvent("Input", tPayload);
			}
		}
		if (gUserCmd.mKeysPressed[i] == 'x')
		{
			unordered_map<string, void*> payload;
			EventManager::GetInstance()->BroadcastEvent("DEBUG", payload);
		}
	}
}

void InputSystem::PauseInput()
{
	int tVectorInput = gUserCmd.mKeysPressed.size();
	int tVectorLastInput = gLastUserCmd.mKeysPressed.size();

	

	for (size_t i = 0; i < tVectorInput; i++)
	{
		bool t_Found = false;
		for (size_t k = 0; k < tVectorLastInput; k++)
		{
			if (gUserCmd.mKeysPressed[i] == gLastUserCmd.mKeysPressed[k])
			{
				t_Found = true;
				k = tVectorLastInput;
			}
		}
		if (!t_Found)
		{
			if (gUserCmd.mKeysPressed[i] == 'p')
			{
				EventManager::Payload tPayload;
				string* tString = new string();
				*tString = "UNPAUSE";
				tPayload["KeyPressed"] = tString;
				EventManager::GetInstance()->BroadcastEvent("Input", tPayload);
			}
		}
	}

	UpDownPressCheck();
	EnterPressCheck();
}

void InputSystem::MenuInput()
{
	UpDownPressCheck();
	EnterPressCheck();
}


void InputSystem::Update(double pDeltaTime)
{
	mKeyState = SDL_GetKeyboardState(NULL);
	CheckKeyboard();

	EntityManager* tEntManager = tEntManager->GetInstance();
	ComponentTable* tCompTable = tCompTable->GetInstance();
	int tMaxEnt = tEntManager->GetLastEntity();

	


	switch (GameStateClass::GetInstance()->GetGameState())
	{
	case MenuScreen:
		MenuInput();
		break;
	case GameScreen:
		for (int i = 0; i < tMaxEnt; i++)
		{
			if (tCompTable->HasComponent(i, ComponentType::LabelType))
			{
				LabelComponent* tLabel = GetComponent<LabelComponent>(i);

				if (tLabel->mLabel == Label::Pad)
				{
					//find input we want to check for TODO:: maybe fix input into bit array?
					PadInput(i);
				}
			}
		}

		GameInput();
		break;
	case DeathScreen:
		MenuInput();
		break;
	case PauseScreen:
		PauseInput();
		break;
	default:
		break;
	}
	gLastUserCmd = gUserCmd;


}

void InputSystem::Pause()
{

}

void InputSystem::Stop()
{

}

void InputSystem::OnEvent(Event* pEvent)
{

}