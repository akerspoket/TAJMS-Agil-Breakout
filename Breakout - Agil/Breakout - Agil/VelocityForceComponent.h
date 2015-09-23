#pragma once

enum ForceType
{
	Percentage,
	ByValue
};

struct VelocityForceComponent
{
	VelocityForceComponent()
	{
		mType = Percentage;
		mAmount = 0.0f;
		mEndValue = 0.0f;
		mIncrease = true;
	}
	ForceType mType;
	float mAmount;
	float mEndValue;
	bool mIncrease;
};