#pragma once
#include "System.h"



class MenuSystem :
	public System
{
public:
	MenuSystem();
	MenuSystem(string pName);
	~MenuSystem();
	virtual void Initialize();
	virtual void Start();
	virtual void Update(double pDeltaTime);
	virtual void Pause();
	virtual void Stop();
	virtual void OnEvent(Event* pEvent);

private:
	int mCurrentButton;
	int mMinButton;
	int mMaxButton;

};

