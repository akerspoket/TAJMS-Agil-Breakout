#pragma once
#include "System.h"
#include <SDL2\SDL.h>


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
	void HandleInput();
	
	SDL_Event mSDLEvent;
	void MoveRight();
	void MoveLeft();
};

