#pragma once
#include "System.h"


class PowerUpSystem:public System
{
public:
	PowerUpSystem();
	PowerUpSystem(string pName);
	~PowerUpSystem();


	void Initialize();
	void Start();
	void Update(double pDeltaTime);
	void Pause();
	void Stop();
	void OnEvent(Event* pEvent);

};

