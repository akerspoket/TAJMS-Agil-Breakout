#pragma once
#include "Event.h"
#include <iostream>

class EventManager;

class System
{
public:
	System();
	~System();

	virtual void Initialize() = 0;
	virtual void Start() = 0;
	virtual void Update(double pDeltaTime) = 0;
	virtual void Pause() = 0;
	virtual void Stop() = 0;
	virtual void OnEvent(Event* pEvent) = 0;

	EventManager* mEventManager;
};

