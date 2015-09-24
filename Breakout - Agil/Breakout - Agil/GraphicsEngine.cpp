#include "GraphicsEngine.h"


//MASTER
GraphicsEngine::GraphicsEngine()
{
	mWVPBufferID.reg = 0;
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
		D3D11_CREATE_DEVICE_DEBUG,
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
	mVertexShader->ShaderHandle->Release();
	mPixelShader->Release();
	mDepthBuffer->Release();
	mDepthView->Release();
	mCubesTexture->Release();
	swapchain->Release();
	backbuffer->Release();
	dev->Release();
	devcon->Release();
}

int GraphicsEngine::CreateTexture(const wchar_t *pFileName)
{
	HRESULT hr;
	ID3D11ShaderResourceView* tCubesTexture = 0;
	hr = CreateDDSTextureFromFile(dev, pFileName, nullptr, &tCubesTexture);
	if (FAILED(hr))
	{
		cout << "Something went wrong while creating texture";
		return -1;
	}
	mTextureBuffers.push_back(tCubesTexture);
	return mTextureBuffers.size() - 1;
}


void GraphicsEngine::InitPipeline()
{
	ID3DBlob *VS, *PS;
	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined(_DEBUG)
	shaderFlags |= D3DCOMPILE_DEBUG;
#endif
	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },

		{ "INSTANCEMATRIX", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1},
		{ "INSTANCEMATRIX", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
		{ "INSTANCEMATRIX", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
		{ "INSTANCEMATRIX", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 }
	};
	CreateShader(VertexShader, &mVertexShader->ShaderHandle, L"VertexShader.hlsl", "VShader", &mVertexShader->InputLayout, ied, ARRAYSIZE(ied));
	CreateShader(PixelShader, &mPixelShader, L"PixelShader.hlsl", "PShader", nullptr,NULL,0);

	SetActiveShader(VertexShader,mVertexShader);
	SetActiveShader(PixelShader, mPixelShader);
}

void GraphicsEngine::InitGraphics(float pFoVAngleY, float pHeight , float pWidth, float pNear, float pFar, float pZPos)
{
	time = 0;
	Vertex OurVertices[] =
	{
		{ -0.5f, 0.5f, -0.5f, 0.0f, 0.0f},
		{ -0.5f, -0.5, -0.5f, 0.0f, 1.0f}, //Framsidan
		{ 0.5f, -0.5f, -0.5f, 1.0f, 1.0f},
		{ 0.5f, 0.5f, -0.5f, 1.0f, 0.0f},

		{ -0.5f, 0.5f, 0.5f, 1.0f, 0.0f }, //4
		{ -0.5f, -0.5, 0.5f, 1.0f, 1.0f }, //5  Baksidan
		{ 0.5f, -0.5f, 0.5f, 0.0f, 1.0f }, //6
		{ 0.5f, 0.5f, 0.5f, 0.0f, 0.0f },  //7


		{ -0.5f, 0.5f, -0.5f, 0.0f,0.0f},  //ovanpå 8
		{ -0.5f, 0.5, 0.5f, 0.0f, 1.0f},   //// 9
		{ 0.5f, 0.5f, 0.5f, 1.0f, 1.0f},   ////10
		{ 0.5f, 0.5f, -0.5f, 1.0f, 0.0f },  //11

		{ -0.5f, -0.5f, 0.5f, 0.0f,0.0f},  //under 12
		{ -0.5f, -0.5, -0.5f, 0.0f, 1.0f },   //// 13
		{ 0.5f, -0.5f, -0.5f, 1.0f, 1.0f },   ////14
		{ 0.5f, -0.5f, 0.5f, 1.0f, 0.0f },  //15

		{ -0.5f, 0.5f, -0.5f, 0.0f,0.0f},  //vänster 16
		{ -0.5f, -0.5, -0.5f, 0.0f, 1.0f },   //// 17
		{ -0.5f, -0.5f, 0.5f, 1.0f, 1.0f },   ////18
		{ -0.5f, 0.5f, 0.5f, 1.0f, 0.0f },  //19

		{ 0.5f, 0.5f, 0.5f, 0.0f,0.0f },  //höger 20
		{ 0.5f, -0.5, 0.5f, 0.0f, 1.0f },   //// 21
		{ 0.5f, -0.5f, -0.5f, 1.0f, 1.0f },   ////22
		{ 0.5f, 0.5f, -0.5f, 1.0f, 0.0f },  //23
	};

	int OurIndices[] =
	{
		2,1,0,
		2,0,3,

		4,5,6,
		4,6,7,

		8,9,10,
		8,10,11,

		12,13,14,
		12,14,15,

		16,17,18,
		16,18,19,

		20,21,22,
		20,22,23


		/*4,0,3,
		4,3,7,
		5,1,2,
		5,2,6,
		0,1,5,
		0,5,4,
		6,2,3,
		6,3,7*/
	};

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(OurVertices);
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	mVertexBufferID = CreateBuffer(bd);

	PushToDevice(mVertexBufferID, &OurVertices, sizeof(OurVertices));

	InstanceBufferType temp;
	for (int i = 0; i < 5; i++)
	{
		XMStoreFloat4x4(&temp.translationMatrices, XMMatrixTranspose(XMMatrixTranslation(1 * (i - 2), 4, 8)));
		mInstanceBuffer.push_back(temp);
	}

	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(InstanceBufferType) * MAX_INSTANCES;//mInstanceBuffer.size();
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	mInstanceBufferID = CreateBuffer(bd);



	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(MatrixBufferType);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	mWVPBufferID.bufferID = CreateBuffer(bd);

	tBufferInfo.world = XMMatrixTranspose(XMMatrixIdentity());
	tBufferInfo.view = XMMatrixTranspose(XMMatrixLookAtLH(XMLoadFloat3(&XMFLOAT3(0.0f, 0.0f, pZPos)), XMLoadFloat3(&XMFLOAT3(0, 0, 1)), XMLoadFloat3(&XMFLOAT3(0, 1, 0))));
	tBufferInfo.projection = XMMatrixTranspose(XMMatrixPerspectiveFovLH(pFoVAngleY, pWidth / pHeight, pNear, pFar));  //XMMatrixPerspectiveFovLH(45.0f, 600.0f / 800.0f, 0.1f, 100));
	PushToDevice(mWVPBufferID.bufferID, &tBufferInfo, sizeof(tBufferInfo), mWVPBufferID.reg,VertexShader);
	HRESULT res;

	D3D11_BUFFER_DESC ibd;
	ZeroMemory(&ibd, sizeof(ibd));

	ibd.Usage = D3D11_USAGE_DYNAMIC;
	ibd.ByteWidth = sizeof(OurIndices);
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	ibd.MiscFlags = 0;
	mIndexBufferID = CreateBuffer(ibd);
	PushToDevice(mIndexBufferID, &OurIndices, sizeof(OurIndices));



	////Ladda In texture
	HRESULT hr;
	mCubesTexture = 0;
	hr = CreateDDSTextureFromFile(dev, L"test2in1pic.dds", nullptr, &mCubesTexture);
	if (FAILED(hr))
	{
		return;
	}
	D3D11_SAMPLER_DESC texSamDesc;
	texSamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	texSamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	texSamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	texSamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	texSamDesc.MipLODBias = 0;
	texSamDesc.MaxAnisotropy = 1;
	texSamDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	texSamDesc.BorderColor[0] = 1.0f;
	texSamDesc.BorderColor[1] = 1.0f;
	texSamDesc.BorderColor[2] = 1.0f;
	texSamDesc.BorderColor[3] = 1.0f;
	texSamDesc.MinLOD = -3.402823466e+38F; // -FLT_MAX
	texSamDesc.MaxLOD = 3.402823466e+38F; // FLT_MAX


	hr = dev->CreateSamplerState(&texSamDesc, &mCubesTexSamplerState);
	if (FAILED(hr))
	{
		return;
	}

	devcon->PSSetShaderResources(0, 1, &mCubesTexture);
	devcon->PSSetSamplers(0, 1, &mCubesTexSamplerState);

}

void GraphicsEngine::RenderFrame(void)
{
	float color[] = { 0.0f,0.2f,0.4f,1.0f };
	unsigned int strides[2];
	unsigned int offsets[2];
	ID3D11Buffer* bufferPointers[2];
	PushToDevice(mInstanceBufferID, mInstanceBuffer.data(), sizeof(InstanceBufferType) * mInstanceBuffer.size());
	// clear the back buffer to a deep blue
	devcon->ClearRenderTargetView(backbuffer, color);
	devcon->ClearDepthStencilView(mDepthView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	strides[0] = sizeof(Vertex);
	strides[1] = sizeof(InstanceBufferType);

	offsets[0] = 0;
	offsets[1] = 0;

	bufferPointers[0] = mBuffers.at(mVertexBufferID);
	bufferPointers[1] = mBuffers.at(mInstanceBufferID);

	devcon->IASetVertexBuffers(0, 2, bufferPointers, strides, offsets);
	devcon->IASetIndexBuffer(mBuffers.at(mIndexBufferID), DXGI_FORMAT_R32_UINT, 0);
	devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//devcon->DrawIndexed(8*3, 0, 0);
#ifdef _WIN32
	devcon->DrawIndexedInstanced(12 * 3, mInstanceBuffer.size(), 0, 0, 0);
#elif __linux__
	cout << "Linux kernel noticed";
#endif
	// do 3D rendering on the back buffer here

	// switch the back buffer and the front buffer

	swapchain->Present(0, 0);
	if (mInstanceBuffer.size() > 0)
	{
		//mInstanceBuffer.pop_back();
	}
}

void GraphicsEngine::DrawObjects(int pMeshType, vector<InstanceBufferType> pInstanceBufferData, int pTextureBuffer)
{

	switch (pMeshType)
	{
	case 0:
	{
		mInstanceBuffer = pInstanceBufferData;
		mVertexBufferID = 0;
		devcon->PSSetShaderResources(0, 1, &mTextureBuffers[pTextureBuffer]);


	} break;
	//case 2 :
	}
		//case 3 :

	unsigned int strides[2];
	unsigned int offsets[2];
	ID3D11Buffer* bufferPointers[2];
	PushToDevice(mInstanceBufferID, mInstanceBuffer.data(), sizeof(InstanceBufferType) * mInstanceBuffer.size());
	// clear the back buffer to a deep blue

	strides[0] = sizeof(Vertex);
	strides[1] = sizeof(InstanceBufferType);

	offsets[0] = 0;
	offsets[1] = 0;

	bufferPointers[0] = mObjectBuffers[pMeshType].vertexDescription;
	bufferPointers[1] = mBuffers.at(mInstanceBufferID);

	devcon->IASetVertexBuffers(0, 2, bufferPointers, strides, offsets);
	devcon->IASetIndexBuffer(mObjectBuffers[pMeshType].indexDescription, DXGI_FORMAT_R32_UINT, 0);
	devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	devcon->DrawIndexedInstanced(12 * 3, mInstanceBuffer.size(), 0, 0, 0);

}
void GraphicsEngine::EndDraw()
{
	swapchain->Present(0, 0);
	float color[] = { 0.0f,0.2f,0.4f,1.0f };
	devcon->ClearRenderTargetView(backbuffer, color);
	devcon->ClearDepthStencilView(mDepthView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}


bool GraphicsEngine::CreateShader(ShaderType pType, void* oShaderHandle, LPCWSTR pShaderFileName, LPCSTR pEntryPoint, ID3D11InputLayout** oInputLayout, D3D11_INPUT_ELEMENT_DESC pInputDescription[], int pArraySize)
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
		HRESULT res = dev->CreateVertexShader(tShader->GetBufferPointer(), tShader->GetBufferSize(), NULL, (ID3D11VertexShader**)oShaderHandle);

		res = dev->CreateInputLayout(pInputDescription, pArraySize, tShader->GetBufferPointer(), tShader->GetBufferSize(), oInputLayout);
		int a = 1;
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

bool GraphicsEngine::SetActiveShader(ShaderType pType, void* oShaderHandle)
{
	switch (pType)
	{
	case GraphicsEngine::VertexShader:
	{
		VertexShaderComponents* tVS = (VertexShaderComponents*)oShaderHandle;
		devcon->VSSetShader(tVS->ShaderHandle, 0, 0);
		devcon->IASetInputLayout(mVertexShader->InputLayout);
	}break;
	case GraphicsEngine::PixelShader:
	{
		devcon->PSSetShader((ID3D11PixelShader*)oShaderHandle, 0, 0);
	}break;
	default:
		break;
	}
	return true;
}

int GraphicsEngine::CreateBuffer(D3D11_BUFFER_DESC pBufferDescription)
{
	ID3D11Buffer* tHolder;
	HRESULT res = dev->CreateBuffer(&pBufferDescription, NULL, &tHolder);
	if (res != S_OK)
	{
		return -1;
	}
	mBuffers.push_back(tHolder);
	int retvalue = mBuffers.size() - 1;
	return retvalue;
}

bool GraphicsEngine::PushToDevice(int pBufferID, void* pDataStart, unsigned int pSize)
{
	D3D11_MAPPED_SUBRESOURCE tMS;
	if (pBufferID > mBuffers.size() - 1 || pBufferID < 0)
	{
#ifdef DEBUG
		cout << "Buffer ID is outside the buffer array";
#endif // DEBUG
		return false;
	}
	ID3D11Buffer* tBufferHandle = mBuffers.at(pBufferID);

	devcon->Map(tBufferHandle, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &tMS);
	memcpy(tMS.pData, pDataStart, pSize);
	devcon->Unmap(tBufferHandle, NULL);

	return true;
}

bool GraphicsEngine::PushToDevice(int pBufferID, void* pDataStart, unsigned int pSize, unsigned int pRegister, ShaderType pType)
{
	bool res = PushToDevice(pBufferID, pDataStart, pSize);
	if (res != true)
{
		return false;
	}
	switch (pType)
	{
	case GraphicsEngine::VertexShader:
	{
		devcon->VSSetConstantBuffers(pRegister, 1, &mBuffers.at(pBufferID));
	}
		break;
	case GraphicsEngine::PixelShader:
	{
		devcon->PSSetConstantBuffers(pRegister, 1, &mBuffers.at(pBufferID));
	}
		break;
	default:
		break;
	}
}

bool GraphicsEngine::PushToDevice(ID3D11Buffer* pBuffer, void* pDataStart, unsigned int pSize)
{
	D3D11_MAPPED_SUBRESOURCE tMS;


	devcon->Map(pBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &tMS);
	memcpy(tMS.pData, pDataStart, pSize);
	devcon->Unmap(pBuffer, NULL);

	return true;

}

int GraphicsEngine::CreateObjectBuffer(D3D11_BUFFER_DESC pVertexBufferDescription, D3D11_BUFFER_DESC pIndexBufferDescription, unsigned int pNumberOfIndices)
{
	ID3D11Buffer* tVertexHolder;
	ID3D11Buffer* tIndexHolder;
	HRESULT res = dev->CreateBuffer(&pVertexBufferDescription, NULL, &tVertexHolder);
	if (res != S_OK)
	{
		return -1;
	}
	res = dev->CreateBuffer(&pIndexBufferDescription, NULL, &tIndexHolder);
	if (res != S_OK)
	{
		return -1;
	}
	mObjectBuffers.push_back(ObjectBufferType(tVertexHolder, tIndexHolder, pNumberOfIndices));
	return mObjectBuffers.size() - 1;

}

void GraphicsEngine::GetTextureID(const char* pTextureName, int& pTextureGroup, int& pTextureID) //vet inte om detta stämmer
{
	if (pTextureName == "Placeholder")
	{
		pTextureGroup = 0;
		pTextureID = 1;
	}
}

int GraphicsEngine::CreateObject(const char* pMeshName)
{

	if (pMeshName == "Box")
	{
		Vertex OurVertices[] =
		{
			{ -0.5f, 0.5f, -0.5f, 0.0f, 0.0f },
			{ -0.5f, -0.5, -0.5f, 0.0f, 1.0f }, //Framsidan
			{ 0.5f, -0.5f, -0.5f, 1.0f, 1.0f },
			{ 0.5f, 0.5f, -0.5f, 1.0f, 0.0f },

			{ -0.5f, 0.5f, 0.5f, 1.0f, 0.0f }, //4
			{ -0.5f, -0.5, 0.5f, 1.0f, 1.0f }, //5  Baksidan
			{ 0.5f, -0.5f, 0.5f, 0.0f, 1.0f }, //6
			{ 0.5f, 0.5f, 0.5f, 0.0f, 0.0f },  //7


			{ -0.5f, 0.5f, -0.5f, 0.0f,0.0f },  //ovanpå 8
			{ -0.5f, 0.5, 0.5f, 0.0f, 1.0f },   //// 9
			{ 0.5f, 0.5f, 0.5f, 1.0f, 1.0f },   ////10
			{ 0.5f, 0.5f, -0.5f, 1.0f, 0.0f },  //11

			{ -0.5f, -0.5f, 0.5f, 0.0f,0.0f },  //under 12
			{ -0.5f, -0.5, -0.5f, 0.0f, 1.0f },   //// 13
			{ 0.5f, -0.5f, -0.5f, 1.0f, 1.0f },   ////14
			{ 0.5f, -0.5f, 0.5f, 1.0f, 0.0f },  //15

			{ -0.5f, 0.5f, -0.5f, 0.0f,0.0f },  //vänster 16
			{ -0.5f, -0.5, -0.5f, 0.0f, 1.0f },   //// 17
			{ -0.5f, -0.5f, 0.5f, 1.0f, 1.0f },   ////18
			{ -0.5f, 0.5f, 0.5f, 1.0f, 0.0f },  //19

			{ 0.5f, 0.5f, 0.5f, 0.0f,0.0f },  //höger 20
			{ 0.5f, -0.5, 0.5f, 0.0f, 1.0f },   //// 21
			{ 0.5f, -0.5f, -0.5f, 1.0f, 1.0f },   ////22
			{ 0.5f, 0.5f, -0.5f, 1.0f, 0.0f },  //23
		};

		int OurIndices[] =
		{
			2,1,0,
			2,0,3,

			4,5,6,
			4,6,7,

			8,9,10,
			8,10,11,

			12,13,14,
			12,14,15,

			16,17,18,
			16,18,19,

			20,21,22,
			20,22,23,
		};

		int rIndex;
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));

		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(OurVertices);
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		D3D11_BUFFER_DESC ibd;
		ZeroMemory(&ibd, sizeof(ibd));

		ibd.Usage = D3D11_USAGE_DYNAMIC;
		ibd.ByteWidth = sizeof(OurIndices);
		ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		ibd.MiscFlags = 0;

		rIndex = CreateObjectBuffer(bd, ibd, ARRAYSIZE(OurIndices));

		PushToDevice(mObjectBuffers[rIndex].indexDescription, &OurIndices, sizeof(OurIndices));

		PushToDevice(mObjectBuffers[rIndex].vertexDescription, &OurVertices, sizeof(OurVertices));

		return rIndex;
	}
	else if (pMeshName == "Sphere")
	{
		//objloader

	}
	else if (pMeshName == "Pad")
	{
		Vertex OurVertices[] =
		{
			{ -0.5f, 0.5f, -0.5f, 0.0f, 0.0f },
			{ -0.5f, -0.5, -0.5f, 0.0f, 1.0f }, //Framsidan
			{ 0.5f, -0.5f, -0.5f, 1.0f, 1.0f },
			{ 0.5f, 0.5f, -0.5f, 1.0f, 0.0f },

			{ -0.5f, 0.5f, 0.5f, 1.0f, 0.0f }, //4
			{ -0.5f, -0.5, 0.5f, 1.0f, 1.0f }, //5  Baksidan
			{ 0.5f, -0.5f, 0.5f, 0.0f, 1.0f }, //6
			{ 0.5f, 0.5f, 0.5f, 0.0f, 0.0f },  //7


			{ -0.5f, 0.5f, -0.5f, 0.0f,0.0f },  //ovanpå 8
			{ -0.5f, 0.5, 0.5f, 0.0f, 1.0f },   //// 9
			{ 0.5f, 0.5f, 0.5f, 1.0f, 1.0f },   ////10
			{ 0.5f, 0.5f, -0.5f, 1.0f, 0.0f },  //11

			{ -0.5f, -0.5f, 0.5f, 0.0f,0.0f },  //under 12
			{ -0.5f, -0.5, -0.5f, 0.0f, 1.0f },   //// 13
			{ 0.5f, -0.5f, -0.5f, 1.0f, 1.0f },   ////14
			{ 0.5f, -0.5f, 0.5f, 1.0f, 0.0f },  //15

			{ -0.5f, 0.5f, -0.5f, 0.0f,0.0f },  //vänster 16
			{ -0.5f, -0.5, -0.5f, 0.0f, 1.0f },   //// 17
			{ -0.5f, -0.5f, 0.5f, 1.0f, 1.0f },   ////18
			{ -0.5f, 0.5f, 0.5f, 1.0f, 0.0f },  //19

			{ 0.5f, 0.5f, 0.5f, 0.0f,0.0f },  //höger 20
			{ 0.5f, -0.5, 0.5f, 0.0f, 1.0f },   //// 21
			{ 0.5f, -0.5f, -0.5f, 1.0f, 1.0f },   ////22
			{ 0.5f, 0.5f, -0.5f, 1.0f, 0.0f },  //23
		};

		int OurIndices[] =
		{
			2,1,0,
			2,0,3,

			4,5,6,
			4,6,7,

			8,9,10,
			8,10,11,

			12,13,14,
			12,14,15,

			16,17,18,
			16,18,19,

			20,21,22,
			20,22,23,
		};

	}
}
