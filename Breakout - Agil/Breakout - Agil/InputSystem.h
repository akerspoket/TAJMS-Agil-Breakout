#pragma once
#include "System.h"
class InputSystem :	public System
{
public:
	InputSystem();
	~InputSystem();

	virtual void Initialize();
	virtual void Start();
	virtual void Update();
	virtual void Pause();
	virtual void Stop();


};

