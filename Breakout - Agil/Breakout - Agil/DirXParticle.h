#pragma once
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
#endif
using namespace std;
class DirXParticle
{
private:
	struct Emitter
	{
		vec3 Position;
		vec3 Color;
		float LifeTime;
		float Density;
		Emitter(vec3 pPosition, vec3 pColor, float pLifeTime, float pDensity)
		{
			Position = pPosition;
			Color = pColor;
			LifeTime = pLifeTime;
			Density = pDensity;	
		}
		Emitter()
		{}
	};
public:
	DirXParticle();
	~DirXParticle();

	void AddNewEmitter(vec3 pPosition, vec3 pColor, float pLifeTime, float pDensity);
	void UpdateEmitters(float pDT);
	void UpdateParticles();
	void DrawParticles();
private:
	vector<Emitter> mEmitters; //Should be sorted on lifetime 
	ID3D11Buffer*  mEmitterBuffer;

};

