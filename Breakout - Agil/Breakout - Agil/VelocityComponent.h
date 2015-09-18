#pragma once
#include "Math.h"

struct VelocityComponent
{
public:
	VelocityComponent()
	{
		//Zero-vector as direction might be a bad idea...
		mDirection = vec3(0.0f, 0.0f, 0.0f);

		mSpeed = 0;
	}
	vec3 mDirection;
	float mSpeed;
};
