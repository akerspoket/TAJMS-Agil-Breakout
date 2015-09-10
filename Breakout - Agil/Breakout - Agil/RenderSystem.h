#pragma once
#include "System.h"

class RenderSystem : public System
{
public:
	RenderSystem();
	~RenderSystem();
	virtual void Initialize();
	virtual void Start();
	virtual void Update(double pDeltaTime);
	virtual void Pause();
	virtual void Stop();
	virtual void OnEvent(Event* pEvent);
};

