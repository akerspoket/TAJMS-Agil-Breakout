#pragma once
#include "GraphicsEngine.h"
#include "TransformComponent.h"
class GraphicsInterface
{
public:
	
	GraphicsInterface();
	~GraphicsInterface();
	int CreateObject(const char* pMeshGroup);
	void DrawObjects(int pMeshGroup, int pTextureGroup[], TransformComponent pTransform[], int pNumberOfMeshes);
	



private: 
	
	GraphicsEngine* mGraphicsEngine;
};

