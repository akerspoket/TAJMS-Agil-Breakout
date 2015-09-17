#pragma once
#include "GraphicsEngine.h"
#include "TransformComponent.h"
class GraphicsInterface
{
public:
	
	GraphicsInterface();
	~GraphicsInterface();
	int CreateObject(const char* pMeshGroup);
	void DrawObjects(int pMeshType, int pTextureGroup[], TransformComponent pTransform[], int pNumberOfIntances);
	



private: 
	
	GraphicsEngine* mGraphicsEngine;
};

