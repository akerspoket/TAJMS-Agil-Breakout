#pragma once
#include "System.h"
#include <SDL2\SDL.h>
#include "EntityManager.h"


class InputSystem :	public System
{
public:
	InputSystem();
	~InputSystem();
	
	void Initialize();
	void Start();
	void Update(double pDeltaTime);
	void Pause();
	void Stop();
	void OnEvent(Event* pEvent);
	const Uint8* mKeyState;
private:
	void CheckKeyboard();
	void HandleInput(EntityID pEntityID);
	
	SDL_Event mSDLEvent;
	void MoveRight(EntityID pEntityID);
	void MoveLeft(EntityID pEntityID);
	void StandStill(EntityID pEntityID);
};

