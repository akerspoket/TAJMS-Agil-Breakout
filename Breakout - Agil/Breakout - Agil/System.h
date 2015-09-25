#pragma once
#include "Event.h"
#include <iostream>

using namespace std;

class EventManager;

class System
{
public:
	System();
	System(string pName);
	~System();

	virtual void Initialize() = 0;
	virtual void Start() = 0;
	virtual void Update(double pDeltaTime) = 0;
	virtual void Pause() = 0;
	virtual void Stop() = 0;
	virtual void OnEvent(Event* pEvent) = 0;
	string GetName();

protected:
	

	EventManager* mEventManager;

private:
	string mSystemName;
};

