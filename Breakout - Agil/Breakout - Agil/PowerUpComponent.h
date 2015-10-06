#pragma once

#include "Math.h"

enum PowerUpType
{
	SpeedUp = 0x01,
};

//enum PowerUpTimerLocation
//{
//	SpeedUpTimerLocation,
//	NumPowerUps,
//};

struct PowerUpComponent
{
	PowerUpComponent()
	{
		powerUps = 0;
	}

	short powerUps;
	//float timers[NumPowerUps];

	bool HasPowerUp(short pMask)
	{
		return ((powerUps & pMask) == pMask); //then there are the components from mask
	}

	void AddPowerUp(short pMask)
	{
		powerUps = powerUps | pMask;
	}
};

