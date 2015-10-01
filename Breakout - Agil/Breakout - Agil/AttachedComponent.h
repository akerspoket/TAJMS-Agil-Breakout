#pragma once

#include "Math.h"

struct AttachedComponent
{
	AttachedComponent()
	{
		relPos = vec3(0, 0, 0);
	}

	vec3 relPos;
	EntityID attachedTo;

};