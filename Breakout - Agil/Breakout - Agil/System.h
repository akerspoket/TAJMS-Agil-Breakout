#pragma once
#include "Event.h"

class System
{
public:
	virtual void Initialize() = 0;
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Pause() = 0;
	virtual void Stop() = 0;
	virtual void OnEvent(Event* pEvent) = 0;
};

