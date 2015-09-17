#pragma once


struct VelocityComponent
{
public:
	VelocityComponent()
	{
		//Zero-vector as direction might be a bad idea...
		mDirection[0] = 0;
		mDirection[1] = 0;
		mDirection[2] = 0;

		mSpeed = 0;
	}
	float mDirection[3];
	float mSpeed;
};
