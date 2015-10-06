#pragma once
#include "System.h"
#include "GraphicsInterface.h"
#include <SDL2\SDL.h>
class RenderSystem : public System
{
public:
	RenderSystem();
	RenderSystem(string pName);
	~RenderSystem();
	virtual void Initialize(); 
	void Initialize(SDL_Window* pWin);
	virtual void Start();
	virtual void Update(double pDeltaTime);
	virtual void Pause();
	virtual void Stop();
	virtual void OnEvent(Event* pEvent);

private:
	GraphicsInterface* mGraphicsInterface;
	int mTempTextId;
};

