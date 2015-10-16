#pragma once
#include "System.h"
class ShipGunSystem :
	public System
{
public:
	ShipGunSystem();
	ShipGunSystem(string pName);
	~ShipGunSystem();


	void Initialize();
	void Start();
	void Update(double pDeltaTime);
	void Pause();
	void Stop();
	void OnEvent(Event* pEvent);
};

