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
	int tVectorLastInput = gUserCmd.mKeysPressedLastUpdate.size();

	if (gUserCmd.mLeftArrowPressed == gUserCmd.mRightArrowPressed )
	{
		StandStill(pEntityID);
	}
	else if (gUserCmd.mLeftArrowPressed == true)
	{
		MoveLeft(pEntityID);
		//cout << "<--";
	}
	else if (gUserCmd.mRightArrowPressed == true)
	{
		MoveRight(pEntityID);
		//cout << "-->";
	}

	if (gUserCmd.mSpaceButtonPressed)
	{
		std::unordered_map<string, void*> tPayLoad; //Sending empty payload has to be fixed...
		EventManager::GetInstance()->BroadcastEvent("LaunchButtonPressed", tPayLoad);
	}

	for (size_t i = 0; i < tVectorInput; i++)
	{
		if (gUserCmd.mKeysPressed[i] == 'a' && gUserCmd.mLeftArrowPressed == false)
		{
			MoveLeft(pEntityID);
			//cout << "A";//Move to the left CODE PLEASE!
		}
		if (gUserCmd.mKeysPressed[i] == 'd' && gUserCmd.mRightArrowPressed == false)
		{
			MoveRight(pEntityID);
			//cout << "D";//Déplacer vers la droite CODE S'IL VOUS PLAÎT !
		}
	}
	
	
	
}

void InputSystem::GameInput()
{
	int tVectorInput = gUserCmd.mKeysPressed.size();
	int tVectorLastInput = gUserCmd.mKeysPressedLastUpdate.size();
	for (size_t i = 0; i < tVectorInput; i++)
	{
		bool t_Found = false;
		for (size_t k = 0; k < tVectorLastInput; k++)
		{
			if (gUserCmd.mKeysPressed[i] == gUserCmd.mKeysPressedLastUpdate[k])
			{
				t_Found = true;
				k = tVectorLastInput;
			}
		}
		if (!t_Found)
		{
			if (gUserCmd.mKeysPressed[i] == 'p')
			{

				cout << "----PAUSE----" << endl;//Déplacer vers la droite CODE S'IL VOUS PAUSE !
				GameStateClass::GetInstance()->SetGameState(GameState::PauseScreen);
			}
		}
	}
}

void InputSystem::PauseInput()
{
	int tVectorInput = gUserCmd.mKeysPressed.size();
	int tVectorLastInput = gUserCmd.mKeysPressedLastUpdate.size();

	for (size_t i = 0; i < tVectorInput; i++)
	{
		bool t_Found = false;
		for (size_t k = 0; k < tVectorLastInput; k++)
		{
			if (gUserCmd.mKeysPressed[i] == gUserCmd.mKeysPressedLastUpdate[k])
			{
				t_Found = true;
				k = tVectorLastInput;
			}
		}
		if (!t_Found)
		{
			if (gUserCmd.mKeysPressed[i] == 'p')
			{
				GameStateClass::GetInstance()->SetGameState(GameState::GameScreen);
				cout << "----UNPAUSE----" << endl;//Déplacer vers la droite CODE S'IL VOUS PAUSE !

			}
		}
	}
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
		break;
	case PauseScreen:
		PauseInput();
		break;
	default:
		break;
	}
	gUserCmd.mKeysPressedLastUpdate = gUserCmd.mKeysPressed;


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