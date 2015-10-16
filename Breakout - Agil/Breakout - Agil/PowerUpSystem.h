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
	void ApplyBallNetPowerUp(float pTime);
	void ApplyPiercingPowerUp(float pTime);
	void ApplyMagnetPowerUp(float pTime);
	void PowerUpSystem::MagnetPowerUp(EntityID pPadID, EntityID pPowerUpID);
	void InvertPowerDown(float pTime);
	void FireBallPowerUp(float pTime);
	void ApplyInvertPowerDown(float pTime);
	void ApplySlowMotionPowerUp(float pTime);
};

