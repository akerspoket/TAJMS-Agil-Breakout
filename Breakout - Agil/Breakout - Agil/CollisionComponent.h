#pragma once
#include "Math.h"

enum CollisionGeo
{
	AABB,
	Sphere
};


struct CollisionComponent
{
	CollisionComponent()
	{
		Dim.x = 0.0f;
		Dim.y = 0.0f;
		mType = AABB;
	}
	CollisionGeo mType;
	//					AABB	|	OOBB	|	SPHERE 
	vec2 Dim;		//	distanceX	distanceX	Radius		
				//	distanceY	distanceY	nothing

};