#pragma once
//#define __linux1__ //FOR DEBUGGING LINUX, REMOVE IN FINAL THINGIE OR FOR WINDOWS DEBUGGING should only be linux
#ifdef __linux1__
#include "OGLGraphicsEngine.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#elif _WIN32
#include "GraphicsEngine.h"
#endif
#include <SDL2/SDL.h>
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

	int CreateObject(string pMeshGroup);
	void DrawInstancedObjects(unsigned int pMeshType, unsigned int pMaterialID, TransformComponent pTransformMatrices[], int pNumberOfInstances); //Draws pNumberofInstances of pMeshType
	int GetTextureID(TextureNames pName);
	int CreateTexture(string pTextureName);
	int CreateText(int pMaxCharacters);
	void DrawThisText(string pText, vec2 pPosition, float pSize, int pSentenceID);
	void EndDraw(); //Call this at the end of drawing multiple objects
	void Initialize(float pFoVAngleY, float pHeight, float pWidth, float pNear, float pFar, float pZPos, SDL_Window* pWin);

	static GraphicsInterface* GetSingleton();
private: 
	GraphicsInterface();
	static GraphicsInterface* mSingleton;
#ifdef __linux1__
	OGLGraphicsEngine* mGraphicsEngine;
#elif _WIN32
	GraphicsEngine* mGraphicsEngine;
#endif

	vector<MaterialStruct> mMaterials;
	map<string, int>mLoadedTextures;
	map<string, int>mLoadedObjects;
};

