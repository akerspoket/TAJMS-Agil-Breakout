#pragma once
#include "Component.h"
class TransformComponent : public Component
{
public:
	TransformComponent();
	~TransformComponent();

	float mPosition[3];
	float mRotation[3];
};

