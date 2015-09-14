#pragma once
#include "System.h"
#include <SDL2\SDL.h>


class InputSystem :	public System
{
public:
	InputSystem();
	~InputSystem();
	static struct UserCmd
	{
		vector<char>mKeysPressed;
		float mXMove;//for the mouse
		float mYMove;//for the mouse
		bool mRightArrowPressed;
		bool mLeftArrowPressed;
		bool mUpArrowPressed;
		bool mDownArrowPressed;

	};
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
	UserCmd mUserCmd;
	SDL_Event mSDLEvent;
	void MoveRight();
	void MoveLeft();
};

