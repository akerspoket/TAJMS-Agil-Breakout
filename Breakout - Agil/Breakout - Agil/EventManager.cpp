#include "EventManager.h"



EventManager::EventManager()
{
}


EventManager::~EventManager()
{
}

void EventManager::BroadcastEvent(Event* pEvent)
{
	EventMap::iterator tIter = mEventMap.find(pEvent->mID);

	//if event exist in map
	if (tIter != mEventMap.end())
	{
		for (int i = 0; i < tIter->second.size(); i++)
		{
			tIter->second[i]->OnEvent(pEvent);
		}
	}
	
	delete pEvent;
}