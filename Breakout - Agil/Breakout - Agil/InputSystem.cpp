#include "InputSystem.h"
#include "EventManager.h"

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
void InputSystem::Update(double pDeltaTime)
{
	char tButton = 'w';
	
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