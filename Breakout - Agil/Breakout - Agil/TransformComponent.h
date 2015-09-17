#pragma once


struct TransformComponent
{
public:
	TransformComponent()
	{
		mPosition[0] = 0;
		mPosition[1] = 0;
		mPosition[2] = 0;

		mQuatRotation[0] = 0;
		mQuatRotation[1] = 0;
		mQuatRotation[2] = 0;
		mQuatRotation[3] = 0;
	}
	float mPosition[3];
	float mQuatRotation[4];
};

