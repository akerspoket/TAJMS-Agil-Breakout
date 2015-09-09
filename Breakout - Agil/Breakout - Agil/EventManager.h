#pragma once
#include "Event.h"
#include "System.h"
#include <unordered_map>

using namespace std;

class EventManager
{
public:
	EventManager();
	~EventManager();

	void BroadcastEvent(Event* pEvent);
private:
	typedef unordered_map<string, vector<System*>> EventMap;
	EventMap mEventMap;

};

