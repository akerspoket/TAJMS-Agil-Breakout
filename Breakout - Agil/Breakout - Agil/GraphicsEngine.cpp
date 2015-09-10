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
	//devcon->OMSetRenderTargets(1, &backbuffer, NULL);


	//DepthBuffer THINGIES
	D3D11_TEXTURE2D_DESC dbdesc;
	ZeroMemory(&dbdesc, sizeof(dbdesc));
	dbdesc.Width = 800;
	dbdesc.Height = 600;
	dbdesc.MipLevels = 1;
	dbdesc.ArraySize = 1;
	dbdesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dbdesc.SampleDesc.Count = 4;
	dbdesc.SampleDesc.Quality = 0;
	dbdesc.Usage = D3D11_USAGE_DEFAULT;
	dbdesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	dbdesc.CPUAccessFlags = 0;
	dbdesc.MiscFlags = 0;

	HRESULT res = dev->CreateTexture2D(&dbdesc, NULL, &mDepthBuffer);

	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));

	descDSV.Format = dbdesc.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	descDSV.Texture2D.MipSlice = 0;


	res = dev->CreateDepthStencilView(mDepthBuffer, &descDSV, &mDepthView);
	devcon->OMSetRenderTargets(1, &backbuffer, mDepthView);


	// Set the viewport
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = 800;
	viewport.Height = 600;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	devcon->RSSetViewports(1, &viewport);
}

void GraphicsEngine::CleanD3D()
{
	// close and release all existing COM objects
	pVS->Release();
	pPS->Release();
	mDepthBuffer->Release();
	mDepthView->Release();
	mIndexBuffer->Release();
	mMatrixBuffer->Release();
	mTransBuffer->Release();
	mMovementBuffer->Release();
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

	CreateShader(VertexShader, &pVS, L"VertexShader.hlsl", "VShader");
	CreateShader(PixelShader, &pPS, L"PixelShader.hlsl", "PShader");

	devcon->VSSetShader(pVS, 0, 0);
	devcon->PSSetShader(pPS, 0, 0);
	devcon->IASetInputLayout(pLayout);

	


}

void GraphicsEngine::InitGraphics()
{
	time = 0;
	Vertex OurVertices[] =
	{
		{ -0.5f, 0.5f, -0.5f,{ 1.0f, 1.0f, 1.0f, 1.0f } },
		{ -0.5f, -0.5, -0.5f,{ 1.0f, 1.0f, 1.0f, 1.0f } },
		{ 0.5f, -0.5f, -0.5f,{ 1.0f, 1.0f, 1.0f, 1.0f } },
		{ 0.5f, 0.5f, -0.5f,{ 1.0f, 1.0f, 1.0f, 1.0f } },
		{ -0.5f, 0.5f, 0.5f,{ 1.0f, 1.0f, 1.0f, 1.0f } },
		{ -0.5f, -0.5, 0.5f,{ 1.0f, 1.0f, 1.0f, 1.0f } },
		{ 0.5f, -0.5f, 0.5f,{ 1.0f, 1.0f, 1.0f, 1.0f } },
		{ 0.5f, 0.5f, 0.5f,{ 1.0f, 1.0f, 1.0f, 1.0f } }
	};

	int OurIndices[] =
	{
		2,1,0,
		2,0,3,
		4,5,6,
		4,6,7,
		4,0,3,
		4,3,7,
		5,1,2,
		5,2,6,
		0,1,5,
		0,5,4,
		6,2,3,
		6,3,7
	};

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(OurVertices);
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	dev->CreateBuffer(&bd, NULL, &pVBuffer);

	D3D11_MAPPED_SUBRESOURCE ms;
	devcon->Map(pVBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
	memcpy(ms.pData, OurVertices, sizeof(OurVertices));
	devcon->Unmap(pVBuffer, NULL);

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

	D3D11_BUFFER_DESC ibd;
	ZeroMemory(&ibd, sizeof(ibd));

	ibd.Usage = D3D11_USAGE_DYNAMIC;
	ibd.ByteWidth = sizeof(OurIndices);
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	ibd.MiscFlags = 0;

	res = dev->CreateBuffer(&ibd, NULL, &mIndexBuffer);

	D3D11_MAPPED_SUBRESOURCE subres;
	devcon->Map(mIndexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &subres);
	memcpy(subres.pData, OurIndices, sizeof(OurIndices));
	devcon->Unmap(mIndexBuffer, NULL);

	InstanceBufferType temp;
	for (int i = 0; i < 5; i++)
	{
		temp.translationMatrices= (XMMatrixTranspose(XMMatrixTranslation(1*(i-2), 4, 8)));
		temp.color[0] = (float)i / 5.0f;
		temp.color[1] = (float)i / 5.0f;
		temp.color[2] = (float)i / 5.0f;
		temp.color[3] = 1;
		mInstanceBuffer.push_back(temp);
	}
	D3D11_BUFFER_DESC transbd;
	ZeroMemory(&transbd, sizeof(transbd));

	transbd.Usage = D3D11_USAGE_DYNAMIC;
	transbd.ByteWidth = sizeof(InstanceBufferType) * mInstanceBuffer.size();
	transbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	transbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	transbd.MiscFlags = 0;
	transbd.StructureByteStride = 0;

	D3D11_MAPPED_SUBRESOURCE subtransres;
	res = dev->CreateBuffer(&transbd, NULL, &mTransBuffer);

	devcon->Map(mTransBuffer, NULL, D3D11_MAP_WRITE_DISCARD,NULL, &subtransres);
	memcpy(subtransres.pData, mInstanceBuffer.data(), sizeof(InstanceBufferType) * mInstanceBuffer.size());
	devcon->Unmap(mTransBuffer, NULL);
	devcon->VSSetConstantBuffers(2, 1, &mTransBuffer);


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
	devcon->ClearDepthStencilView(mDepthView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	devcon->IASetVertexBuffers(0, 1, &pVBuffer, &stride, &offset);
	devcon->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//devcon->DrawIndexed(8*3, 0, 0);
	devcon->DrawIndexedInstanced(12 * 3, 5, 0, 0, 0);
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
	dataPointer->projection = XMMatrixTranspose(XMMatrixPerspectiveFovLH(45.0f, 600.0f/800.0f, 0.1f, 100));
	//dataPointer->projection = XMMatrixTranspose(XMMatrixIdentity());
	devcon->Unmap(mMatrixBuffer, 0);

	bufferNumber = 0;

	devcon->VSSetConstantBuffers(bufferNumber, 1, &mMatrixBuffer);

	result = devcon->Map(mMovementBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource2);

	MovementBufferType* dPointer;
	time += 0.001;
	dPointer = (MovementBufferType*)mappedResource2.pData;
	dPointer->time = time;

	/*MovementBufferType *dPointer = new MovementBufferType;

	time += 0.001;
	dPointer->time = time;

	memcpy(mappedResource2.pData, dPointer, sizeof(MovementBufferType));*/
	devcon->Unmap(mMovementBuffer, 0);


	bufferNumber = 1;

	devcon->VSSetConstantBuffers(bufferNumber, 1, &mMovementBuffer);
}

bool GraphicsEngine::CreateShader(ShaderType pType, void* oShaderHandle, LPCWSTR pShaderFileName, LPCSTR pEntryPoint)
{
	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined(_DEBUG)
	shaderFlags |= D3DCOMPILE_DEBUG;
#endif
	ID3DBlob *tShader;

	switch (pType)
	{
	case GraphicsEngine::VertexShader:
	{
		D3DCompileFromFile(pShaderFileName, 0, 0, pEntryPoint, "vs_5_0", shaderFlags, 0, &tShader, 0);
		dev->CreateVertexShader(tShader->GetBufferPointer(), tShader->GetBufferSize(), NULL, (ID3D11VertexShader**)oShaderHandle);
		D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		dev->CreateInputLayout(ied, 2, tShader->GetBufferPointer(), tShader->GetBufferSize(), &pLayout);

	}break;
	case GraphicsEngine::PixelShader:
	{
		D3DCompileFromFile(pShaderFileName, 0, 0, pEntryPoint, "ps_5_0", shaderFlags, 0, &tShader, 0);
		dev->CreatePixelShader(tShader->GetBufferPointer(), tShader->GetBufferSize(), NULL, (ID3D11PixelShader**)oShaderHandle);
	}break;
	default:
		break;
	}
	return true;
}