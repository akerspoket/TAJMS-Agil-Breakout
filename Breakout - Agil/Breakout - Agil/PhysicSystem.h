#pragma once
#include "System.h"
#include "CollisionComponent.h"
#include "TransformComponent.h"
#include "Constants.h"

class PhysicSystem : public System
{
public:
	PhysicSystem();
	PhysicSystem(string pName);
	~PhysicSystem();

	void Initialize();
	void Start();
	void Update(double pDeltaTime);
	void Pause();
	void Stop();
	void OnEvent(Event* pEvent);

private:
	void HandleCollision(EntityID pEntityID1, EntityID pEntityID2, CollisionComponent* pColl1, TransformComponent* pTrans1, CollisionComponent* pColl2, TransformComponent* pTrans2);
	void AABBvsAABB(EntityID pEntityID1, EntityID pEntityID2, CollisionComponent* pColl1, TransformComponent* pTrans1, CollisionComponent* pColl2, TransformComponent* pTrans2);
	bool ExplosiveCollisionCheck(CollisionComponent* pColSphere, TransformComponent* pTransSphere, CollisionComponent* pColAABB, TransformComponent* pTransAABB);
	void SphereVsSphere(EntityID pEntityID1, EntityID pEntityID2, CollisionComponent* pColl1, TransformComponent* pTrans1, CollisionComponent* pColl2, TransformComponent* pTrans2);
	void AABBvsSphere(EntityID pEntityID1, EntityID pEntityID2, CollisionComponent* pColl1, TransformComponent* pTrans1, CollisionComponent* pColl2, TransformComponent* pTrans2);
	float mMinAngle;

};

