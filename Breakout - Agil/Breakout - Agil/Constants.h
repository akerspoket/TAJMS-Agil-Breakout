#pragma once

#define MAX_NUM_ENTITIES 1024
#define NUM_OF_COMOPNENTS 4
typedef int EntityID;

enum ComponentType
{
	PhysicType,			//0
	TransformType,		//1
	RenderType,			//2
	SoundType			//3
};