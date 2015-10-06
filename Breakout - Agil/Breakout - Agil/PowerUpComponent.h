#pragma once

#include "Math.h"

enum PowerUpType
{
	SpeedUp = 0x01,
};

struct PowerUpComponent
{
	PowerUpComponent()
	{
		powerUps = 0;
	}

	short powerUps;

	bool HasPowerUp(short pMask)
	{
		return ((powerUps & pMask) == pMask); //then there are the components from mask
	}

	void AddPowerUp(short pMask)
	{
		powerUps = powerUps | pMask;
	}
};

