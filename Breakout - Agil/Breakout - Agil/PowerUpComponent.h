#pragma once

#include "Math.h"

enum PowerUpType
{
	SpeedUp = 0x01,
	BallNet = 0x02,
	Piercing = 0x04,
	MagnetPUp = 0x08,
	InvertDown = 0x10,

	SlowMotion = 0x40,
};

enum PowerUpTimerLocation
{
	SpeedUpLoc,
	BallNetLoc,
	PiercingLoc,
	MagnetPUpLoc,
	InvertDownLoc,

	SlowMotionLoc,
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

