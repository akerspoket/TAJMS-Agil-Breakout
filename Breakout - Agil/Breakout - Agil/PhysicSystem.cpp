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
	if ((pTrans1->mPosition[0] - pTrans2->mPosition[0]) > (pColl1->X + pColl2->X))
	{
		return false;
	}
	if ((pTrans1->mPosition[1] - pTrans2->mPosition[1]) > (pColl1->X + pColl2->X))
	{
		return false;
	}
	/*if ((pTrans1->mPosition[0] - pTrans2->mPosition[0]) > (pColl1->X + pColl2->X))  //for the Z, don't think we will use it?
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
	return false;
}

bool PhysicSystem::AABBvsOOBB(CollisionComponent* pColl1, TransformComponent* pTrans1, CollisionComponent* pColl2, TransformComponent* pTrans2)
{
	return false;
}

bool PhysicSystem::AABBvsSphere(CollisionComponent* pColl1, TransformComponent* pTrans1, CollisionComponent* pColl2, TransformComponent* pTrans2)
{
	return false;
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
		if (pColl1->mType == CollisionGeo::AABB)
		{
			rCollided = AABBvsAABB(pColl1, pTrans1, pColl2, pTrans2);
		}
		else if (pColl1->mType == CollisionGeo::OOBB)
		{
			rCollided = AABBvsOOBB(pColl1, pTrans1, pColl2, pTrans2);
		}
		else if (pColl1->mType == CollisionGeo::Sphere)
		{
			rCollided = AABBvsSphere(pColl1, pTrans1, pColl2, pTrans2);
		}
	}
	else if (pColl1->mType == CollisionGeo::OOBB)
	{
		if (pColl1->mType == CollisionGeo::AABB)
		{
			rCollided = AABBvsOOBB(pColl2, pTrans2, pColl1, pTrans1);
		}
		else if (pColl1->mType == CollisionGeo::OOBB)
		{
			rCollided = OOBBvsOOBB(pColl1, pTrans1, pColl2, pTrans2);
		}
		else if (pColl1->mType == CollisionGeo::Sphere)
		{
			rCollided = OOBBvsSphere(pColl1, pTrans1, pColl2, pTrans2);
		}
	}
	else if (pColl1->mType == CollisionGeo::Sphere)
	{
		if (pColl1->mType == CollisionGeo::AABB)
		{
			rCollided = AABBvsSphere(pColl2, pTrans2, pColl1, pTrans1);
		}
		else if (pColl1->mType == CollisionGeo::OOBB)
		{
			rCollided = OOBBvsSphere(pColl2, pTrans2, pColl1, pTrans1);
		}
		else if (pColl1->mType == CollisionGeo::Sphere)
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

			tTrans->mPosition[0] += tVel->mDirection[0] * tVel->mSpeed*pDeltaTime;
			tTrans->mPosition[1] += tVel->mDirection[1] * tVel->mSpeed*pDeltaTime;
			tTrans->mPosition[2] += tVel->mDirection[2] * tVel->mSpeed*pDeltaTime;

			//DEBUG
			if (GetComponent<LabelComponent>(i)->mLabel == Label::Pad)
				cout << "Position for pad is: " << tTrans->mPosition[0] << " " << tTrans->mPosition[1] << endl;
			//END DEBUG

			if (GetComponent<LabelComponent>(i)->mLabel == Label::Pad)
			{
				GetComponent<VelocityComponent>(i)->mDirection[0] = 0;
				GetComponent<VelocityComponent>(i)->mDirection[1] = 0;
				GetComponent<VelocityComponent>(i)->mDirection[2] = 0;
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