#pragma once
#include "System.h"
class AttachSystem :public System
{
public:
	AttachSystem();
	AttachSystem(string pName);
	~AttachSystem();

	void Initialize();
	void Start();
	void Update(double pDeltaTime);
	void Pause();
	void Stop();
	void OnEvent(Event* pEvent);
};

