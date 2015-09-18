#pragma once
#include "Math.h"

struct TransformComponent
{
public:
	TransformComponent()
	{
		mPosition = vec3(0.0f, 0.0f, 0.0f);
		mQuatRotation = vec4(0.0f, 0.0f, 0.0f, 0.0f);
	}
	vec3 mPosition;
	vec4 mQuatRotation;
};

