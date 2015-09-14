#pragma once

#define MAX_NUM_ENTITIES 1024
#define NUM_OF_COMPONENTS 4
typedef int EntityID;

//if more then 16 component-types, need to change the table from short->int
enum ComponentType
{
	PhysicType,			//0
	TransformType,		//1
	RenderType,			//2
	SoundType			//3
};