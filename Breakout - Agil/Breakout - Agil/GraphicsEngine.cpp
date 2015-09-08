#include "GraphicsEngine.h"



GraphicsEngine::GraphicsEngine()
{
}


GraphicsEngine::~GraphicsEngine()
{
}

void GraphicsEngine::InitD3D(HWND hWnd) 
{
	// create a struct to hold information about the swap chain
	DXGI_SWAP_CHAIN_DESC scd;

	// clear out the struct for use
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	// fill the swap chain description struct
	scd.BufferCount = 1;                                    // one back buffer
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
	scd.OutputWindow = hWnd;                                // the window to be used
	scd.SampleDesc.Count = 4;                               // how many multisamples
	scd.Windowed = TRUE;                                    // windowed/full-screen mode

															// create a device, device context and swap chain using the information in the scd struct
	D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		NULL,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&swapchain,
		&dev,
		NULL,
		&devcon);

	ID3D11Texture2D *pBackBuffer;
	swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	dev->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
	pBackBuffer->Release();
	devcon->OMSetRenderTargets(1, &backbuffer, NULL);

	// Set the viewport
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = 800;
	viewport.Height = 600;

	devcon->RSSetViewports(1, &viewport);
}

void GraphicsEngine::CleanD3D()
{
	// close and release all existing COM objects
	pVS->Release();
	pPS->Release();
	swapchain->Release();
	backbuffer->Release();
	dev->Release();
	devcon->Release();
}

void GraphicsEngine::InitPipeline()
{
	ID3DBlob *VS, *PS;
	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined(_DEBUG)
	shaderFlags |= D3DCOMPILE_DEBUG;
#endif
	
	D3DCompileFromFile(L"VertexShader.hlsl", 0, 0, "VShader", "vs_4_0", shaderFlags, 0, &VS, 0);
	D3DCompileFromFile(L"PixelShader.hlsl", 0, 0, "PShader", "ps_4_0", shaderFlags, 0, &PS, 0);

	dev->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &pVS);
	dev->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pPS);

	devcon->VSSetShader(pVS, 0, 0);
	devcon->PSSetShader(pPS, 0, 0);
	
	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	dev->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);
	devcon->IASetInputLayout(pLayout);



}

void GraphicsEngine::InitGraphics()
{
	time = 0;
	Vertex OurVertices[] =
	{
		{ 0.0f, 6.0f, 2.0f,{ 1.0f, 0.0f, 0.0f, 1.0f } },
		{ 6.0f, -6.0, 2.0f,{ 0.0f, 1.0f, 0.0f, 1.0f } },
		{ -6.0f, -6.0f, 2.0f,{ 0.0f, 0.0f, 1.0f, 1.0f } }
	};

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(Vertex) * 3;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	dev->CreateBuffer(&bd, NULL, &pVBuffer);

	D3D11_BUFFER_DESC mbd;
	ZeroMemory(&mbd, sizeof(mbd));

	mbd.Usage = D3D11_USAGE_DYNAMIC;
	mbd.ByteWidth = sizeof(MatrixBufferType);
	mbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	mbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	mbd.MiscFlags = 0;
	mbd.StructureByteStride = 0;
	mMatrixBuffer = 0;
	HRESULT res = dev->CreateBuffer(&mbd, NULL, &mMatrixBuffer);

	D3D11_BUFFER_DESC mvbd;
	ZeroMemory(&mvbd, sizeof(mvbd));

	mvbd.Usage = D3D11_USAGE_DYNAMIC;
	mvbd.ByteWidth = sizeof(MovementBufferType);
	mvbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	mvbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	mvbd.MiscFlags = 0;
	mvbd.StructureByteStride = 0;
	mMovementBuffer = 0;
	res = dev->CreateBuffer(&mvbd,NULL, &mMovementBuffer);

	if (FAILED(res))
	{
		return;
	}

	D3D11_MAPPED_SUBRESOURCE ms;
	devcon->Map(pVBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
	memcpy(ms.pData, OurVertices, sizeof(OurVertices));
	devcon->Unmap(pVBuffer, NULL);

	world = XMMatrixIdentity();
	view = XMMatrixLookAtLH(XMLoadFloat3(&XMFLOAT3(0.0f, 0.0f, 0.0f)), XMLoadFloat3(&XMFLOAT3(0, 0, 1)), XMLoadFloat3(&XMFLOAT3(0, 1, 0)));
	proj = XMMatrixPerspectiveLH(60.0f, 60.0f, 0, 100);

	SetShaderInputs();
}

void GraphicsEngine::RenderFrame(void)
{
	
	SetShaderInputs();
	float color[4];
	
	// Setup the color to clear the buffer to.
	color[0] = 0.0f;
	color[1] = 0.2f;
	color[2] = 0.4f;
	color[3] = 1.0f;
	// clear the back buffer to a deep blue
	devcon->ClearRenderTargetView(backbuffer, color);


	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	devcon->IASetVertexBuffers(0, 1, &pVBuffer, &stride, &offset);
	devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	devcon->Draw(3, 0);
	// do 3D rendering on the back buffer here
	
	// switch the back buffer and the front buffer
	swapchain->Present(0, 0);
}

void GraphicsEngine::SetShaderInputs()
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	D3D11_MAPPED_SUBRESOURCE mappedResource2;
	MatrixBufferType* dataPointer;
	UINT bufferNumber;

	//Transpose for some reason...

	result = devcon->Map(mMatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	if (FAILED(result))
	{
		return;
	}

	dataPointer = (MatrixBufferType*)mappedResource.pData;

	dataPointer->world =XMMatrixTranspose(XMMatrixIdentity());
	dataPointer->view = XMMatrixTranspose(XMMatrixLookAtLH(XMLoadFloat3(&XMFLOAT3(0.0f, 0.0f, 0.0f)), XMLoadFloat3(&XMFLOAT3(0, 0, 1)), XMLoadFloat3(&XMFLOAT3(0, 1, 0))));
	dataPointer->projection = XMMatrixTranspose(XMMatrixPerspectiveLH(20.0f, 20.0f, 1, 100));

	devcon->Unmap(mMatrixBuffer, 0);

	bufferNumber = 0;

	devcon->VSSetConstantBuffers(bufferNumber, 1, &mMatrixBuffer);

	result = devcon->Map(mMovementBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource2);

	MovementBufferType* dPointer;
	time += 0.001;
	dPointer = (MovementBufferType*)mappedResource2.pData;
	dPointer->time = time;

	devcon->Unmap(mMovementBuffer, 0);
	bufferNumber = 1;

	devcon->VSSetConstantBuffers(bufferNumber, 1, &mMovementBuffer);
}