#pragma once
#include "System.h"
class InputSystem :	public System
{
public:
	InputSystem();
	~InputSystem();

	void Initialize();
	void Start();
	void Update();
	void Pause();
	void Stop();
	void OnEvent(Event* pEvent);

};

