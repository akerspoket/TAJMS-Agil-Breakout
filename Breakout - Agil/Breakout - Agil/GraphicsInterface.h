#pragma once
//#define __linux__ //FOR DEBUGGING LINUX, REMOVE IN FINAL THINGIE OR FOR WINDOWS DEBUGGING
#ifdef __linux__
#include "OGLGraphicsEngine.h"
#elif _WIN32
#include "GraphicsEngine.h"
#endif

#include <map>
#include <vector>
#include "TransformComponent.h"

using namespace std;
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
	void Initialize(float pFoVAngleY, float pHeight, float pWidth, float pNear, float pFar, float pZPos);

	void Initialize();
	static GraphicsInterface* GetSingleton();
private: 
	GraphicsInterface();
	static GraphicsInterface* mSingleton;
#ifdef __linux__
	OGLGraphicsEngine* mGraphicsEngine;
#elif _WIN32
	GraphicsEngine* mGraphicsEngine;
#endif

	vector<MaterialStruct> mMaterials;
	map<const wchar_t*, int>mLoadedTextures;
	map<const char*, int>mLoadedObjects;
};

