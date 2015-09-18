#pragma once
#include "System.h"
#include "CollisionComponent.h"
#include "TransformComponent.h"

class PhysicSystem : public System
{
public:
	PhysicSystem();
	~PhysicSystem();

	void Initialize();
	void Start();
	void Update(double pDeltaTime);
	void Pause();
	void Stop();
	void OnEvent(Event* pEvent);

private:
	bool CheckCollision(CollisionComponent* pColl1, TransformComponent* pTrans1, CollisionComponent* pColl2, TransformComponent* pTrans2);
	bool AABBvsAABB(CollisionComponent* pColl1, TransformComponent* pTrans1, CollisionComponent* pColl2, TransformComponent* pTrans2);
	bool OOBBvsOOBB(CollisionComponent* pColl1, TransformComponent* pTrans1, CollisionComponent* pColl2, TransformComponent* pTrans2);
	bool SphereVsSphere(CollisionComponent* pColl1, TransformComponent* pTrans1, CollisionComponent* pColl2, TransformComponent* pTrans2);
	bool AABBvsOOBB(CollisionComponent* pColl1, TransformComponent* pTrans1, CollisionComponent* pColl2, TransformComponent* pTrans2);
	bool AABBvsSphere(CollisionComponent* pColl1, TransformComponent* pTrans1, CollisionComponent* pColl2, TransformComponent* pTrans2);
	bool OOBBvsSphere(CollisionComponent* pColl1, TransformComponent* pTrans1, CollisionComponent* pColl2, TransformComponent* pTrans2);

};

