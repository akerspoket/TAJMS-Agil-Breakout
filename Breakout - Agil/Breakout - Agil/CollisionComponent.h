#pragma once


enum CollisionGeo
{
	AABB,
	OOBB,
	Sphere
};


struct CollisionComponent
{
	CollisionComponent()
	{
		X = 0.0f;
		Y = 0.0f;
		mType = AABB;
	}
	CollisionGeo mType;
	//					AABB	|	OOBB	|	SPHERE 
	float X;		//	distanceX	distanceX	Radius		
	float Y;		//	distanceY	distanceY	nothing

};