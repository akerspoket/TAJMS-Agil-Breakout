#pragma once
#include "System.h"
#include "SoundEngine.h"
#ifndef LinuxSound
#define LinuxSound
#endif
class SoundSystem :
	public System
{
public:
	SoundSystem();
	SoundSystem(string pName);
	~SoundSystem();
	virtual void Initialize();
	virtual void Start();
	virtual void Update(double pDeltaTime);
	virtual void Pause();
	virtual void Stop();
	virtual void OnEvent(Event* pEvent);
private:
	SoundEngine* mSoundEngine;
};

