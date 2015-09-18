#include "PhysicSystem.h"
#include "EventManager.h"
#include "EntityManager.h"
#include "ComponentTable.h"
#include "StorageShelf.h"
#include "PhysicComponent.h"
#include "VelocityComponent.h"
#include "LabelComponent.h"


PhysicSystem::PhysicSystem()
{

}

PhysicSystem::~PhysicSystem()
{

}

void PhysicSystem::Initialize()
{
	mEventManager = mEventManager->GetInstance();
	mEventManager->Subscribe("DebugTest", this);
}

void PhysicSystem::Start()
{

}

bool PhysicSystem::AABBvsAABB(CollisionComponent* pColl1, TransformComponent* pTrans1, CollisionComponent* pColl2, TransformComponent* pTrans2)
{
	//check if distance between their positions is greater then their both half widths
	if ((pTrans1->mPosition.x - pTrans2->mPosition.x) > (pColl1->X + pColl2->X))
	{
		return false;
	}
	if ((pTrans1->mPosition.y - pTrans2->mPosition.y) > (pColl1->X + pColl2->X))
	{
		return false;
	}
	/*if ((pTrans1->mPosition.z - pTrans2->mPosition.z) > (pColl1->X + pColl2->X))  //for the Z, don't think we will use it?
	{
		return false;
	}*/

	return true;
}

bool PhysicSystem::OOBBvsOOBB(CollisionComponent* pColl1, TransformComponent* pTrans1, CollisionComponent* pColl2, TransformComponent* pTrans2)
{
	return false;
}

bool PhysicSystem::SphereVsSphere(CollisionComponent* pColl1, TransformComponent* pTrans1, CollisionComponent* pColl2, TransformComponent* pTrans2)
{
	float tLength = (pTrans1->mPosition - pTrans2->mPosition).Abs();

	float tSumRadius = pColl1->X + pColl2->X;

	//check if distance between points is less then sumradius
	bool rCollided = tLength < tSumRadius;

	return rCollided;
}

bool PhysicSystem::AABBvsOOBB(CollisionComponent* pColl1, TransformComponent* pTrans1, CollisionComponent* pColl2, TransformComponent* pTrans2)
{
	return false;
}

//from https://studiofreya.com/3d-math-and-physics/sphere-vs-aabb-collision-detection-test/


float CheckDirection(float pPosInDirection, float pBoxSideMin, float pBoxSideMax)
{
	float out = 0;
	float v = pPosInDirection;

	if (v < pBoxSideMin)
	{
		float val = (pBoxSideMin - v);
		out += val*val;
	}
	if (v > pBoxSideMax)
	{
		float val = (v - pBoxSideMax);
		out += val*val;
	}
	return out;
}

float SquareDistToPoint(CollisionComponent* pColl1, TransformComponent* pTrans1, CollisionComponent* pColl2, TransformComponent* pTrans2)
{
	float out = 0.0f;
	out += CheckDirection(pTrans2->mPosition.x, pTrans1->mPosition.x - pColl1->X, pTrans1->mPosition.x + pColl1->X);
	out += CheckDirection(pTrans2->mPosition.y, pTrans1->mPosition.y - pColl1->Y, pTrans1->mPosition.y + pColl1->Y);

	return out;
}

bool PhysicSystem::AABBvsSphere(CollisionComponent* pColl1, TransformComponent* pTrans1, CollisionComponent* pColl2, TransformComponent* pTrans2)
{
	float tSquareDistance = SquareDistToPoint(pColl1, pTrans1, pColl2, pTrans2);

	bool tCollide = tSquareDistance <= (pColl2->X * pColl2->X);

	return tCollide;
}

bool PhysicSystem::OOBBvsSphere(CollisionComponent* pColl1, TransformComponent* pTrans1, CollisionComponent* pColl2, TransformComponent* pTrans2)
{
	return false;
}

bool PhysicSystem::CheckCollision(CollisionComponent* pColl1, TransformComponent* pTrans1, CollisionComponent* pColl2, TransformComponent* pTrans2)
{
	bool rCollided = true;
	if (pColl1->mType == CollisionGeo::AABB)
	{
		if (pColl2->mType == CollisionGeo::AABB)
		{
			rCollided = AABBvsAABB(pColl1, pTrans1, pColl2, pTrans2);
		}
		else if (pColl2->mType == CollisionGeo::OOBB)
		{
			rCollided = AABBvsOOBB(pColl1, pTrans1, pColl2, pTrans2);
		}
		else if (pColl2->mType == CollisionGeo::Sphere)
		{
			rCollided = AABBvsSphere(pColl1, pTrans1, pColl2, pTrans2);
		}
	}
	else if (pColl1->mType == CollisionGeo::OOBB)
	{
		if (pColl2->mType == CollisionGeo::AABB)
		{
			rCollided = AABBvsOOBB(pColl2, pTrans2, pColl1, pTrans1);
		}
		else if (pColl2->mType == CollisionGeo::OOBB)
		{
			rCollided = OOBBvsOOBB(pColl1, pTrans1, pColl2, pTrans2);
		}
		else if (pColl2->mType == CollisionGeo::Sphere)
		{
			rCollided = OOBBvsSphere(pColl1, pTrans1, pColl2, pTrans2);
		}
	}
	else if (pColl1->mType == CollisionGeo::Sphere)
	{
		if (pColl2->mType == CollisionGeo::AABB)
		{
			rCollided = AABBvsSphere(pColl2, pTrans2, pColl1, pTrans1);
		}
		else if (pColl2->mType == CollisionGeo::OOBB)
		{
			rCollided = OOBBvsSphere(pColl2, pTrans2, pColl1, pTrans1);
		}
		else if (pColl2->mType == CollisionGeo::Sphere)
		{
			rCollided = SphereVsSphere(pColl1, pTrans1, pColl2, pTrans2);
		}
	}

	return rCollided;
}

void PhysicSystem::Update(double pDeltaTime)
{
	EntityManager* tEntManager = tEntManager->GetInstance();
	ComponentTable* tCompTable = tCompTable->GetInstance();
	
	tEntManager->RemoveEntity(0);
	tEntManager->RemoveEntity(1);

	//TESTS JAWS TESTING WARNING TEST TEST TEST
	EntityID tID = tEntManager->AddEntity();
	tCompTable->AddComponent(tID, CollisionType | TransformType);
	TransformComponent* tTrans = GetComponent<TransformComponent>(tID);
	CollisionComponent* tColl = GetComponent<CollisionComponent>(tID);
	tTrans->mPosition = vec3();
	tColl->mType = CollisionGeo::AABB;
	tColl->X = 1;
	tColl->Y = 1;

	tID = tEntManager->AddEntity();
	tCompTable->AddComponent(tID, CollisionType | TransformType);
	tTrans = GetComponent<TransformComponent>(tID);
	tColl = GetComponent<CollisionComponent>(tID);
	tColl->mType = CollisionGeo::Sphere;
	tColl->X = 1.0f;
	tTrans->mPosition = vec3(0.0f, 2.0f, 0);

	int tMaxEnt = tEntManager->GetLastEntity();


	//Update position with velocity
	for (int i = 0; i < tMaxEnt; i++)
	{

		//Ensure that relevant components exist
		short tFlags = VelocityType | TransformType;
		if (tCompTable->HasComponent(i, tFlags))
		{
			TransformComponent* tTrans = GetComponent<TransformComponent>(i);
			VelocityComponent* tVel = GetComponent<VelocityComponent>(i);

			tTrans->mPosition.x += tVel->mDirection.x * tVel->mSpeed*pDeltaTime;
			tTrans->mPosition.y += tVel->mDirection.y * tVel->mSpeed*pDeltaTime;
			tTrans->mPosition.z += tVel->mDirection.z * tVel->mSpeed*pDeltaTime;

			//DEBUG
			if (GetComponent<LabelComponent>(i)->mLabel == Label::Pad)
				cout << "Position for pad is: " << tTrans->mPosition.x << " " << tTrans->mPosition.y << endl;
			//END DEBUG

			if (GetComponent<LabelComponent>(i)->mLabel == Label::Pad)
			{
				GetComponent<VelocityComponent>(i)->mDirection.x = 0.0f;
				GetComponent<VelocityComponent>(i)->mDirection.y = 0.0f;
				GetComponent<VelocityComponent>(i)->mDirection.z = 0.0f;
			}
		}
	}

	//checking static collisions, not counting in their moved distance as a box
	for (int i = 0; i < tMaxEnt; i++)
	{
		if (tCompTable->HasComponent(i, CollisionType | TransformType))
		{
			CollisionComponent* tColl1 = GetComponent<CollisionComponent>(i);
			TransformComponent* tTrans1 = GetComponent<TransformComponent>(i);

			for (int k = i + 1; k < tMaxEnt; k++)
			{
				if (tCompTable->HasComponent(k, CollisionType | TransformType))
				{
					CollisionComponent* tColl2 = GetComponent<CollisionComponent>(k);
					TransformComponent* tTrans2 = GetComponent<TransformComponent>(k);

					if (CheckCollision(tColl1, tTrans1, tColl2, tTrans2))
					{
						//move back to the collision
					}
				}
			}
		}
	}
}

void PhysicSystem::Pause()
{

}

void PhysicSystem::Stop()
{

}

void PhysicSystem::OnEvent(Event* pEvent)
{

}