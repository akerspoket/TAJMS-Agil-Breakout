#pragma once
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <windows.h>
#include <windowsx.h>
#include <d3d11_1.h>
#include <DirectXMath.h>
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3dcompiler.h>
#include <vector>
#include "DDSTextureLoader.h"

using namespace DirectX;
using namespace std;

struct Vertex
{
	float x, y, z;
	float color[4];
};

struct MatrixBufferType
{
	XMMATRIX world;
	XMMATRIX view;
	XMMATRIX projection;
};

struct MovementBufferType
{
	float time;
	XMFLOAT3 filler;
};

struct InstanceBufferType
{
	 XMMATRIX translationMatrices;
	 float color[4];
};


class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();
	// global declarations

	IDXGISwapChain *swapchain;           
	ID3D11Device *dev;                   
	ID3D11DeviceContext *devcon;         
	ID3D11RenderTargetView *backbuffer;  
	ID3D11VertexShader *pVS;    // the vertex shader
	ID3D11PixelShader *pPS;     // the pixel shader			
	ID3D11Buffer *pVBuffer;    // global
	ID3D11InputLayout *pLayout;    // global
	ID3D11Buffer *mMatrixBuffer;
	ID3D11Buffer *mMovementBuffer;
	ID3D11Buffer *mIndexBuffer;
	ID3D11Texture2D *mDepthBuffer;
	ID3D11DepthStencilView *mDepthView;

	XMMATRIX world;
	XMMATRIX view;
	XMMATRIX proj;
	ID3D11Buffer *mTransBuffer;
	XMMATRIX mTranslationMatrices[5];
	vector <InstanceBufferType> mInstanceBuffer;
	float time;

	void InitD3D(HWND hWnd);     // sets 
	void InitPipeline();
	void CleanD3D(void);         // close
	void RenderFrame(void);
	void InitGraphics();
	void SetShaderInputs();

private:
	enum ShaderType { VertexShader, PixelShader };
	bool CreateShader(ShaderType pType, void* oShaderHandle, LPCWSTR pShaderFileName, LPCSTR pEntryPoint);

	ID3D11ShaderResourceView* mCubesTexture;
	ID3D11SamplerState* mCubesTexSamplerState;
};

