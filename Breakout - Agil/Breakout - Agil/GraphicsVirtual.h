#pragma once
#include <vector>

class GraphicsVirtual
{
public:
	virtual void InitD3D() = 0;     // sets 
	virtual void InitPipeline() = 0;
	virtual void CleanD3D(void) = 0;         // close
	virtual void RenderFrame(void) = 0;
	virtual void InitGraphics() = 0;
	virtual int CreateObject(const char* pMeshName) = 0;
	virtual void GetTextureID(const char* pTetureName, int& pTextureGroup, int& pTextureID) = 0;
	virtual int CreateTexture(const wchar_t *pFileName) = 0;
	virtual void EndDraw() = 0;

};
