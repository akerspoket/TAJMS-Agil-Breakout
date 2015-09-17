#include "InputSystem.h"
#include "EventManager.h"
#include "StorageShelf.h"
#include "LabelComponent.h"
#include "VelocityComponent.h"
#include "ComponentTable.h"
#include "StorageShelf.h"

using namespace std;

InputSystem::InputSystem()
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
	if (mKeyState[SDL_SCANCODE_ESCAPE])
	{
		cout << "Stäng av programmet";
	}
}

void InputSystem::MoveRight(EntityID pEntityID)
{
	ComponentTable* tCompTable = tCompTable->GetInstance();

	tCompTable->AddComponent(pEntityID, ComponentType::VelocityType);

	VelocityComponent* tVel = GetComponent<VelocityComponent>(pEntityID);
	tVel->mDirection[0] = 1.0f;
	tVel->mDirection[1] = 0.0f;
	tVel->mDirection[2] = 0.0f;
}

void InputSystem::MoveLeft(EntityID pEntityID)
{
	ComponentTable* tCompTable = tCompTable->GetInstance();
	
	tCompTable->AddComponent(pEntityID, ComponentType::VelocityType);
	
	VelocityComponent* tVel = GetComponent<VelocityComponent>(pEntityID);
	tVel->mDirection[0] = -1.0f;
	tVel->mDirection[1] = 0.0f;
	tVel->mDirection[2] = 0.0f;
}
void InputSystem::HandleInput(EntityID pEntityID)
{
	int tVectorInput = gUserCmd.mKeysPressed.size();
	if (gUserCmd.mLeftArrowPressed == true)
	{
		MoveLeft(pEntityID);
		//cout << "<--";
	}
	if (gUserCmd.mRightArrowPressed == true)
	{
		MoveRight(pEntityID);
		//cout << "-->";
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
void InputSystem::Update(double pDeltaTime)
{
	mKeyState = SDL_GetKeyboardState(NULL);
	CheckKeyboard();
	//HandleInput();

	EntityManager* tEntManager = tEntManager->GetInstance();
	ComponentTable* tCompTable = tCompTable->GetInstance();
	int tMaxEnt = tEntManager->GetLastEntity();

	for (int i = 0; i < tMaxEnt; i++)
	{
		if (tCompTable->HasComponent(i, ComponentType::LabelType))
		{
			LabelComponent* tLabel = GetComponent<LabelComponent>(i);

			if (tLabel->mLabel == Label::Pad)
			{
				//find input we want to check for TODO:: maybe fix input into bit array?
				HandleInput(i);
			}
		}
	}


	//cout << "running input system";
	//EventManager::Payload tPayload;
	//tPayload["test"] = MessageInt(5);

 //	void* tDebugData = malloc(4);
	//void* tDebugData2 = malloc(4);
	//*(int*)tDebugData = 4;
	//*(int*)tDebugData2 = 5;

	////memcpy(tDebugData, &data, 4);
	////memcpy(tDebugData2, &data2, 4);
	//tPayload["Debugdata"] = tDebugData;
	//tPayload["Test"] = tDebugData2;
	//cout << "Sending event";
	//mEventManager->BroadcastEvent("DebugTest", tPayload);
	//cout << "event sent, resuming input system update";




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