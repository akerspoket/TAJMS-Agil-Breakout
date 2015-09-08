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

using namespace DirectX;

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

	XMMATRIX world;
	XMMATRIX view;
	XMMATRIX proj;
	float time;

	void InitD3D(HWND hWnd);     // sets 
	void InitPipeline();
	void CleanD3D(void);         // close
	void RenderFrame(void);
	void InitGraphics();
	void SetShaderInputs();
};

