#include "EventManager.h"

EventManager* EventManager::mSingleton = nullptr;

EventManager* EventManager::GetInstance()
{
	if (mSingleton == nullptr)
	{
		mSingleton = new EventManager();
	}

	return mSingleton;
}

EventManager::EventManager()
{
}


EventManager::~EventManager()
{
}

void EventManager::BroadcastEvent(string pID, Payload pPayload)
{
	Event tEvent = Event();
	tEvent.mID = pID;
	tEvent.mPayload = pPayload;

	EventMap::iterator tIter = mEventMap.find(tEvent.mID);

	//if event exist in map send it to subscribed systems
	if (tIter != mEventMap.end())
	{
		for (unsigned int i = 0; i < tIter->second.size(); i++)
		{
			tIter->second[i]->OnEvent(&tEvent);
		}
	}

	//delete allocated memory for event sent
	for (Payload::iterator iter = tEvent.mPayload.begin(); iter != tEvent.mPayload.end(); ++iter)
	{
		delete iter->second;
	}
}

void EventManager::Subscribe(string pEventID, System* pSystem)
{
	mEventMap[pEventID].push_back(pSystem);
}