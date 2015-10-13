#include "DirXParticle.h"



DirXParticle::DirXParticle()
{
}


DirXParticle::~DirXParticle()
{
}

void DirXParticle::AddNewEmitter(vec3 pPosition, vec3 pColor, float pLifeTime, float pDensity)
{
	mEmitters.push_back( Emitter(pPosition, pColor, pLifeTime, pDensity));
}
void DirXParticle::UpdateEmitters(float pDT)
{
	for (int i = 0; i < mEmitters.size(); i++)
	{
		mEmitters[i].LifeTime -= pDT;
		if (mEmitters[i].LifeTime <= 0.0f)
		{
			mEmitters.erase(mEmitters.begin() + i);
			i--;
		}
	}
}
void DirXParticle::UpdateParticles()
{}
void DirXParticle::DrawParticles() 
{

}