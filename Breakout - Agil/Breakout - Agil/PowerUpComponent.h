#pragma once

#include "Math.h"

enum PowerUpType
{
	SpeedUp = 0x01,
	BallNet = 0x02,
	Piercing = 0x04,
	PUP4 = 0x08,
	PUP5 = 0x10,
};

enum PowerUpTimerLocation
{
	SpeedUpLoc,
	BallNetLoc,
	PiercingLoc,
	NumPowerUps,
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
	float timers[NumPowerUps];

	bool HasPowerUp(short pMask)
	{
		return ((powerUps & pMask) == pMask);
	}

	void AddPowerUp(short pMask)
	{
		powerUps = powerUps | pMask;
	}
	void RemovePowerUp(short pMask)
	{
		short tAnd = powerUps & pMask;
		powerUps = powerUps ^ tAnd;
	}
};

