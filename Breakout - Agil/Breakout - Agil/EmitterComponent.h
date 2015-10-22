#pragma once
#include "Math.h"
#define MAX_PARTICLE_EMITTER 7

struct EmitterComponent
{
	EmitterComponent()
	{
		for (int i = 0; i < MAX_PARTICLE_EMITTER; i++)
		{
			Attached[i] = false;
			EmitterID[i] = -1;
			Timers[i] = 0;
		}
	}
	bool Attached[MAX_PARTICLE_EMITTER];
	int EmitterID[MAX_PARTICLE_EMITTER];
	float Timers[MAX_PARTICLE_EMITTER];
};
