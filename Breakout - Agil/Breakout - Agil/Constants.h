#pragma once

#define MAX_NUM_ENTITIES 1024
#define NUM_OF_COMPONENTS 4
#define ERROR_MESH_INDEX 0

typedef int EntityID;


//if more then 16 component-types, need to change the table from short->int
//if you add component add code to CreateEntity function in EntityFactory
enum ComponentType
{
	PhysicType = 0x01,
	TransformType = 0x02,
	MeshType = 0x04,
	LabelType = 0x08,
	VelocityType = 0x10,
	CollisionType = 0x20,
	VelocityForceType = 0x40,
	SoundCollisionType = 0x80,
	AttachedType = 0x100,
	ScoreValueType = 0x200,
	MenyButtonType = 0x400,
	PowerUpType = 0x800,
	PowerUpContainType = 0x1000,
	EmitterType = 0x2000,
};

// 0x01 ==   1 == "00000001"
// 0x02 ==   2 == "00000010"
// 0x04 ==   4 == "00000100"
// 0x08 ==   8 == "00001000"
// 0x10 ==  16 == "00010000"
// 0x20 ==  32 == "00100000"
// 0x40 ==  64 == "01000000"
// 0x80 == 128 == "10000000"
// 0x100 = 256 = "100000000"
// 0x200
// 0x400
// 0x800
// 0x1000
// 0xetc
// options == 0x01 | 0x08 | 0x10 == "00011001"