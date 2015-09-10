#pragma once


struct TransformComponent
{
public:
	TransformComponent()
	{
		mPosition[0] = 0;
		mPosition[1] = 0;
		mPosition[2] = 0;

		mRotation[0] = 0;
		mRotation[1] = 0;
		mRotation[2] = 0;
	}
	float mPosition[3];
	float mRotation[3];
};

