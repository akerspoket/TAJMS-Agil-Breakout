#pragma once
#include "System.h"
#include "Math.h"

class ShipGunSystem :
	public System
{
public:
	ShipGunSystem();
	ShipGunSystem(string pName);
	~ShipGunSystem();


	void Initialize();
	void Start();
	void Update(double pDeltaTime);
	void Pause();
	void Stop();
	void OnEvent(Event* pEvent);

private:
	vec3 CalculateCannonDirection(vec2 ballIntersectPos, vec2 pBallPos, vec2 pPadPos);

	vec2 mBallIntersectPos;
	float mCannonFollowSpeed;
	float mCannonPos;

	float mCannonAngle;
	float mCannonAngleFollowSpeed;

	float mFireForce;
	float mFireForceRemaining;
	float mFireForceDecay;
	float mFireAngle;
};

