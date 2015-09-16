#pragma once
#include "Constants.h"

struct MeshComponent
{
	MeshComponent()
	{
		mMeshID = ERROR_MESH_INDEX;
	}
	unsigned int mMeshID;
	unsigned int mMaterialID;
};