#pragma once
#include "System.h"
#include "Constants.h"

class VelocitySystem : public System
{
public:
	VelocitySystem();
	VelocitySystem(string pName);
	~VelocitySystem();

	void Initialize();
	void Start();
	void Update(double pDeltaTime);
	void Pause();
	void Stop();
	void OnEvent(Event* pEvent);
};

