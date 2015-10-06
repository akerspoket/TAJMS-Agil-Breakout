#pragma once
#include "System.h"

class ScoreSystem : public System
{
public:
	ScoreSystem();
	ScoreSystem(string pName);
	~ScoreSystem();

	void Initialize();
	void Start();
	void Update(double pDeltaTime);
	void Pause();
	void Stop();
	void OnEvent(Event* pEvent);


private:
	int mScore;
	void SendScore();
};

