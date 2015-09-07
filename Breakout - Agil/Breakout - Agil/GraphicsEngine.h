#pragma once
#include <windows.h>
#include <windowsx.h>
#include <d3d11_1.h>
#include <DirectXMath.h>

#pragma comment (lib, "d3d11.lib")
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
										 
	void InitD3D(HWND hWnd);     // sets 
	void CleanD3D(void);         // close
	void RenderFrame(void);

};

