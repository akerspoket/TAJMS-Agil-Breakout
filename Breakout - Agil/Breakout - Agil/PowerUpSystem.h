#pragma once
#include "System.h"
#include "Constants.h"


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

private:
	void RemovePower(EntityID id, short pMask);
	void BallNetPowerUp(float pTime);
	void PiercingPowerUp(float pTime);
	void MagnetPowerUp(float pTime);
	void PowerUpSystem::MagnetPowerUp(EntityID pPadID, EntityID pPowerUpID);
};

