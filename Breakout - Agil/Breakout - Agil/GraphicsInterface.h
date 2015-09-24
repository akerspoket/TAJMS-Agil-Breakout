#pragma once
#include "GraphicsEngine.h"
#include <map>
#include "TransformComponent.h"
class GraphicsInterface
{
public:
	struct MaterialStruct
	{
		int textureID;
	}; 
	enum TextureNames
	{
		BRICK,
		ELEPHANT
	};
	GraphicsInterface();
	~GraphicsInterface();

	int CreateObject(const char* pMeshGroup);
	void DrawInstancedObjects(unsigned int pMeshType, unsigned int pMaterialID, TransformComponent pTransformMatrices[], int pNumberOfInstances); //Draws pNumberofInstances of pMeshType
	int GetTextureID(TextureNames pName);
	int CreateTexture(const wchar_t* pTextureName);
	void EndDraw(); //Call this at the end of drawing multiple objects
	void Initialize(float pFoVAngleY, float pHeight, float pWidth, float pNear, float pFar, float pZPos);

private: 


	GraphicsEngine* mGraphicsEngine;
	vector<MaterialStruct> mMaterials;
	map<const wchar_t*, int>mLoadedTextures;
	map<const char*, int>mLoadedObjects;
};

