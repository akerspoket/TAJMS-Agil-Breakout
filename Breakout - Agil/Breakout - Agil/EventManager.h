#pragma once
#include "Event.h"
#include "System.h"
#include <unordered_map>

using namespace std;

class EventManager
{
public:
	typedef unordered_map<string, void*> Payload;
	static EventManager* GetInstance();

	void BroadcastEvent(string pID, Payload pPayload);
	void Subscribe(string pEventID, System* pSystem);

private:
	EventManager();
	~EventManager();
	static EventManager* mSingleton;
	typedef unordered_map<string, vector<System*>> EventMap;
	EventMap mEventMap;

};

