#pragma once
#define MAX_NUMBER_OF_PARTICLES 500 //remember to update this on the particle update shader too, for now atleast
#define MAX_NUMBER_OF_EMITTERS 30
#include "Math.h"
#include <vector>

#ifdef _WIN32
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

using namespace std;
class DirXParticle
{
private:
	struct Emitter
	{
		vec3 Position;
		float LifeTime;
		vec3 Color;	
		float Density;
		vec3 Velocity;
		float ParticleLifeTime;
		float filler;
		float SpeedMulti;
		float Spread;
		float Size;
		Emitter(vec3 pPosition, vec3 pColor, float pLifeTime, float pDensity,vec3 pVelocity ,float pParticleLifeTime, float pSpeedMulti, float pSpread, float pStartSize)
		{
			Position = pPosition;
			Color = pColor;
			LifeTime = pLifeTime;
			Density = pDensity;	
			ParticleLifeTime = pParticleLifeTime;
			Velocity = pVelocity;
			filler = 0;
			SpeedMulti = pSpeedMulti;
			Spread = pSpread;
			Size = pStartSize;
		}
		Emitter()
		{}
	};
	struct ParticleInfo
	{
		vec3 Position;
		vec3 Direction;
		vec3 Color;
		float Speed;
		float LifeTime;
		float LifeLength;
		float Size;
		float Blend;
		float StartSize;
	};
	struct NumberOfEmittersType
	{
		int Number;
		vec3 Filler;
	};
	ID3D11Device *dev;
	ID3D11DeviceContext *devcon;
	ID3D11ComputeShader* mEmitterComputeShader;
	ID3D11ComputeShader* mParticleUpdateComputeShader;
	ID3D11VertexShader* mParticleVertexShader;
	ID3D11GeometryShader* mParticleGeoShader;
	ID3D11PixelShader* mParticlePixelShader;
	ID3D11ShaderResourceView* mParticleBufferView;
	ID3D11UnorderedAccessView* mEmitterOutputUAV;
	ID3D11ShaderResourceView* mEmitterOutput;

public:
	DirXParticle();
	~DirXParticle();

	void Initialize(ID3D11Device *pDev, ID3D11DeviceContext *pDevcon);
	int AddNewEmitter(vec3 pPosition, vec3 pColor, float pLifeTime, float pDensity,vec3 pVelocity, float pParticleLifeTime, float pSpeedMulti, float pSpread, float pStartSize);
	void UpdateEmitters(float pDT);
	int ChangeEmitterPos(vec3 pPosition, int pEmitterID, vec3 pVelocity);
	void UpdateParticles();
	void DrawParticles(ID3D11Buffer* pMatrixBuffer);
private:
	vector<Emitter> mEmitters; //Should be sorted on lifetime 
	ID3D11Buffer*  mEmitterBuffer;
	ID3D11Buffer*  mNumberOfEmitterBuffer;
	ID3D11Buffer* mParticleBuffer;
	ID3D11Buffer* mRandomBuffer;
	ID3D11InputLayout* mParticleLayout;

	ID3D11PixelShader* mPixelShader;
	NumberOfEmittersType mNumberOfEmitters;
};

#endif