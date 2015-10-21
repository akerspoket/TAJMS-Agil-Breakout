#pragma once
#include "System.h"
#include "PowerUpComponent.h"

using namespace std;

class EnemySystem :	public System
{
public:
	EnemySystem();
	EnemySystem(string pName);
	~EnemySystem();

	virtual void Initialize();
	virtual void Start();
	virtual void Update(double pDeltaTime);
	virtual void Pause();
	virtual void Stop();
	virtual void OnEvent(Event* pEvent);
private:
	vector<short> mAviablePowerUps;
	vector<float> mPowerUpTimes;
	float mCooldown;
};

