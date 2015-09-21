#pragma once
#ifdef _WIN32
#include "GraphicsEngine.h"
#elif __linux__
#include "OGLGraphicsEngine.h"
#endif

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

	~GraphicsInterface();

	int CreateObject(const char* pMeshGroup);
	void DrawInstancedObjects(unsigned int pMeshType, unsigned int pMaterialID, TransformComponent pTransformMatrices[], int pNumberOfInstances); //Draws pNumberofInstances of pMeshType
	int GetTextureID(TextureNames pName);
	int CreateTexture(const wchar_t* pTextureName);
	void EndDraw(); //Call this at the end of drawing multiple objects
	void Initialize();
	static GraphicsInterface* GetSingleton();
private: 
	GraphicsInterface();
	static GraphicsInterface* mSingleton;
#ifdef _WIN32
	GraphicsEngine* mGraphicsEngine;
#elif __linux__
	OGLGraphicsEngine* mGraphicsEngine;
#endif

	vector<MaterialStruct> mMaterials;
	map<const wchar_t*, int>mLoadedTextures;
	map<const char*, int>mLoadedObjects;
};

