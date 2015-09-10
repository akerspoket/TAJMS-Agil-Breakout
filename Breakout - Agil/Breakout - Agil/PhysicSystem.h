#pragma once
#include "System.h"

class PhysicSystem : public System
{
public:
	PhysicSystem();
	~PhysicSystem();

	void Initialize();
	void Start();
	void Update(double pDeltaTime);
	void Pause();
	void Stop();
	void OnEvent(Event* pEvent);
};

