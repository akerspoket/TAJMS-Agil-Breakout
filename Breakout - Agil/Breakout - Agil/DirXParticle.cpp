#include "DirXParticle.h"
#include <stdlib.h>
#include <time.h>


DirXParticle::DirXParticle()
{
}


DirXParticle::~DirXParticle()
{
}

int DirXParticle::AddNewEmitter(vec3 pPosition, vec3 pColor, float pLifeTime, float pDensity, vec3 pVelocity, float pParticleLifeTime, float pSpeedMulti, float pSpread, float pStartSize)
{
	for (size_t i = 0; i < mEmitters.size(); i++)
	{
		if (mEmitters[i].LifeTime < 0)
		{
			mEmitters[i] = Emitter(pPosition, pColor, pLifeTime, pDensity, pVelocity, pParticleLifeTime, pSpeedMulti, pSpread, pStartSize);
			return i;
		}
	}
	mEmitters.push_back(Emitter(pPosition, pColor, pLifeTime, pDensity, pVelocity, pParticleLifeTime, pSpeedMulti, pSpread, pStartSize));
	return mEmitters.size() - 1;
}

int DirXParticle::ChangeEmitterPos(vec3 pPosition, int pEmitterID, vec3 pVelocity)
{
	if (mEmitters.size() - 1 >= pEmitterID)
	{
		mEmitters[pEmitterID].Position = pPosition;
		mEmitters[pEmitterID].Velocity = pVelocity;
		return pEmitterID;
	}
	else
	{
		return -1;
	}

}

void DirXParticle::UpdateEmitters(float pDT)
{
	vector<vec4> randomDirections;
	
	for (int i = 0; i < mEmitters.size(); i++)
	{
		mEmitters[i].LifeTime -= pDT;
	}
	for (int i = 0; i < 20; i++)
	{
		float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX/ 2.0f) - 1;
		float y= static_cast <float> (rand()) / static_cast <float> (RAND_MAX / 2.0f) - 1;
		float z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / 2.0f) - 1;
		float w = 0;
		randomDirections.push_back(vec4(x, y, z,w));
		//randoma å pushbacka till mRandomVector

	}


	D3D11_MAPPED_SUBRESOURCE tMS;

	devcon->Map(mEmitterBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &tMS);
	memcpy(tMS.pData, mEmitters.data(), sizeof(Emitter) * mEmitters.size());
	devcon->Unmap(mEmitterBuffer, NULL);
	devcon->CSSetConstantBuffers(1, 1, &mEmitterBuffer);

	mNumberOfEmitters.Number = mEmitters.size();
	devcon->Map(mNumberOfEmitterBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &tMS);
	memcpy(tMS.pData, &mNumberOfEmitters, sizeof(mNumberOfEmitters));
	devcon->Unmap(mNumberOfEmitterBuffer, NULL);
	devcon->CSSetConstantBuffers(2, 1, &mNumberOfEmitterBuffer);

	devcon->Map(mRandomBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &tMS);
	memcpy(tMS.pData, randomDirections.data(), sizeof(vec3) * randomDirections.size());
	devcon->Unmap(mRandomBuffer, NULL);
	devcon->CSSetConstantBuffers(3, 1, &mRandomBuffer);



	devcon->CSSetShader(mEmitterComputeShader, 0, 0);
	ID3D11UnorderedAccessView* uav[] = { mEmitterOutputUAV };

	devcon->CSSetUnorderedAccessViews(0, ARRAYSIZE(uav), uav, NULL);



	devcon->Dispatch(1, 1, 1);

	devcon->CSSetShader(nullptr, 0, 0);

	ID3D11UnorderedAccessView* tRemoveUAV[] = { NULL };
	devcon->CSSetUnorderedAccessViews(0, ARRAYSIZE(tRemoveUAV), tRemoveUAV, NULL);
}
void DirXParticle::UpdateParticles()
{
	devcon->CSSetShader(mParticleUpdateComputeShader, 0, 0);
	ID3D11UnorderedAccessView* uav[] = { mEmitterOutputUAV };

	devcon->CSSetUnorderedAccessViews(0, ARRAYSIZE(uav), uav, NULL);

	devcon->Dispatch(1, 1, 1);

	devcon->CSSetShader(nullptr, 0, 0);

	ID3D11UnorderedAccessView* tRemoveUAV[] = { NULL };
	devcon->CSSetUnorderedAccessViews(0, ARRAYSIZE(tRemoveUAV), tRemoveUAV, NULL);
}
void DirXParticle::DrawParticles(ID3D11Buffer* pMatrixBuffer) 
{
	devcon->VSSetShader(mParticleVertexShader, 0, 0);
	devcon->GSSetShader(mParticleGeoShader, 0, 0);
	devcon->PSSetShader(mParticlePixelShader, 0, 0);
	devcon->VSSetShaderResources(0, 1, &mParticleBufferView);

	//devcon->IASetVertexBuffers(0, 1, nullptr, 0, 0);
	devcon->IASetInputLayout(NULL);
	devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	devcon->GSSetConstantBuffers(0, 1, &pMatrixBuffer);
	devcon->Draw(500, 0);
	ID3D11ShaderResourceView* tNullRV = NULL;
	devcon->VSSetShaderResources(0, 1, &tNullRV);
	devcon->VSSetShader(nullptr, 0, 0);
	devcon->GSSetShader(nullptr, 0, 0);
	devcon->PSSetShader(nullptr, 0, 0);


}

void  DirXParticle::Initialize(ID3D11Device *pDev, ID3D11DeviceContext *pDevcon)
{
	srand(time(NULL));
	DWORD shaderFlags =
		D3DCOMPILE_ENABLE_STRICTNESS |
		D3DCOMPILE_IEEE_STRICTNESS |
		//D3DCOMPILE_WARNINGS_ARE_ERRORS |
		D3DCOMPILE_PREFER_FLOW_CONTROL;
#if defined( DEBUG ) || defined(_DEBUG)
	shaderFlags |= D3DCOMPILE_DEBUG;
	shaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	dev = pDev;
	devcon = pDevcon;
	HRESULT res;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	bd.ByteWidth = sizeof(ParticleInfo) * MAX_NUMBER_OF_PARTICLES;
	bd.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
	//vbd.CPUAccessFlags = 0;
	bd.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	bd.StructureByteStride = sizeof(ParticleInfo);

	res = dev->CreateBuffer(&bd, nullptr, &mParticleBuffer);


	ID3DBlob *tShader;
	D3DCompileFromFile(L"EmitterComputeShader.hlsl", 0, 0, "main", "cs_5_0", shaderFlags, 0, &tShader, 0);
	res = dev->CreateComputeShader(tShader->GetBufferPointer(), tShader->GetBufferSize(), NULL, &mEmitterComputeShader);
	res = dev->CreateUnorderedAccessView(mParticleBuffer, NULL, &mEmitterOutputUAV);
	res = dev->CreateShaderResourceView(mParticleBuffer, NULL, &mParticleBufferView);
	D3DCompileFromFile(L"ParticleVertexShader.hlsl", 0, 0, "main", "vs_5_0", shaderFlags, 0, &tShader, 0);
	res = dev->CreateVertexShader(tShader->GetBufferPointer(), tShader->GetBufferSize(), NULL, &mParticleVertexShader); 
	D3DCompileFromFile(L"ParticleUpdateComputeShader.hlsl", 0, 0, "main", "cs_5_0", shaderFlags, 0, &tShader, 0);
	res = dev->CreateComputeShader(tShader->GetBufferPointer(), tShader->GetBufferSize(), NULL, &mParticleUpdateComputeShader);
	//D3D11_INPUT_ELEMENT_DESC ied[] =
	//{
	//	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//	{ "DIRECTION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//	{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//	{ "SPEED", 0, DXGI_FORMAT_R32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//	{ "LIFETIME", 0, DXGI_FORMAT_R32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//	{ "LIFELENGTH", 0, DXGI_FORMAT_R32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }

	//};
	//res = dev->CreateInputLayout(ied, ARRAYSIZE(ied), tShader->GetBufferPointer(), tShader->GetBufferSize(), &mParticleLayout);

	D3DCompileFromFile(L"ParticleGeometryShader.hlsl", 0, 0, "main", "gs_5_0", shaderFlags, 0, &tShader, 0);
	res = dev->CreateGeometryShader(tShader->GetBufferPointer(), tShader->GetBufferSize(), NULL, &mParticleGeoShader);

	D3DCompileFromFile(L"ParticlePixelShader.hlsl", 0, 0, "main", "ps_5_0", shaderFlags, 0, &tShader, 0);
	res = dev->CreatePixelShader(tShader->GetBufferPointer(), tShader->GetBufferSize(), NULL, &mParticlePixelShader);





	


	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.ByteWidth = sizeof(Emitter) * MAX_NUMBER_OF_EMITTERS;


	res = dev->CreateBuffer(&bd, NULL, &mEmitterBuffer);
	if (res != S_OK)
	{
		return;
	}

	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.ByteWidth = sizeof(NumberOfEmittersType);


	res = dev->CreateBuffer(&bd, NULL, &mNumberOfEmitterBuffer);
	if (res != S_OK)
	{
		return;
	}

	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.ByteWidth = sizeof(vec4) * 20;
	//bd.StructureByteStride = sizeof(vec3);

	res = dev->CreateBuffer(&bd, NULL, &mRandomBuffer);
	if (res != S_OK)
	{
		return;
	}

}