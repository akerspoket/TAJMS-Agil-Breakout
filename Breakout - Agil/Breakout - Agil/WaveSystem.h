#pragma once
#include "System.h"
#include "Constants.h"
using namespace std;
class WaveSystem:public System
{
public:
	WaveSystem();
	WaveSystem(string pName);
	~WaveSystem();
	void Initialize();
	void Start();
	void Update(double pDeltaTime);
	void Pause();
	void Stop();
	void OnEvent(Event* pEvent);
private:
	float mTimer;
};

