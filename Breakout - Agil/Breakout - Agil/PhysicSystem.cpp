#include "PhysicSystem.h"
#include "EventManager.h"
#include "EntityManager.h"
#include "ComponentTable.h"
#include "StorageShelf.h"
#include "PhysicComponent.h"
#include "VelocityComponent.h"
#include "VelocityForceComponent.h"
#include "SoundCollisionComponent.h"
#include "AttachedComponent.h"
#include "LabelComponent.h"

#include <cmath> //needed for linux... come on!


PhysicSystem::PhysicSystem()
{

}

PhysicSystem::PhysicSystem(string pName):System(pName)
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

void PhysicSystem::AABBvsAABB(EntityID pEntityID1, EntityID pEntityID2, CollisionComponent* pColl1, TransformComponent* pTrans1, CollisionComponent* pColl2, TransformComponent* pTrans2)
{
	//check if distance between their positions is greater then their both half widths
	if (abs(pTrans1->mPosition.x - pTrans2->mPosition.x) > (pColl1->Dim.x + pColl2->Dim.x))
	{
		return;
	}
	if (abs(pTrans1->mPosition.y - pTrans2->mPosition.y) > (pColl1->Dim.y + pColl2->Dim.y))
	{
		return;
	}
	/*if (abs(pTrans1->mPosition.z - pTrans2->mPosition.z) > (pColl1->X + pColl2->X))  //for the Z, don't think we will use it?
	{
		return false;
	}*/

	//handle collisison
}

void PhysicSystem::SphereVsSphere(EntityID pEntityID1, EntityID pEntityID2, CollisionComponent* pColl1, TransformComponent* pTrans1, CollisionComponent* pColl2, TransformComponent* pTrans2)
{
	float tLength = (pTrans1->mPosition - pTrans2->mPosition).Abs();

	float tSumRadius = pColl1->Dim.x + pColl2->Dim.x;

	//check if distance between points is less then sumradius
	bool rCollided = tLength < tSumRadius;

	if (rCollided)
	{
		//Special case if component is ball
		if (GetComponent<LabelComponent>(pEntityID2)->mLabel == Label::Ball)
		{
			VelocityComponent* ballVel = GetComponent<VelocityComponent>(pEntityID2);
			vec2 tPadSphereOffset = vec2(0, -5); //how large we want the sphere to be
			vec2 tBallPos = vec3toVec2(pTrans2->mPosition);
			vec2 tPadSpherePos = vec3toVec2(pTrans1->mPosition) + tPadSphereOffset;
			vec2 collision = tBallPos - tPadSpherePos;
			float distance = collision.Abs();
			
			collision = collision * (1 / distance);
			vec2 tDir = vec3toVec2(ballVel->mDirection);
			float aci = tDir*collision;
			float bci = 0;

			float acf = bci;
			float bcf = aci;

			tDir += collision*(0 - aci);
			tDir -= collision*(bcf - 0);
				
			float tMinAngle = 0.3;
			if (tDir.y < tMinAngle) //exit angle too low
			{
				float tExitX = 1;
				if (tDir.x < 0)
					tExitX = -1;
				tDir = vec2(tExitX, tMinAngle).Normalize();
			}

			ballVel->mDirection = vec2toVec3(tDir);
		
		}
	}

	
}

//from https://studiofreya.com/3d-math-and-physics/sphere-vs-aabb-collision-detection-test/

//returns the square distance from the closest plane in one axis in AABB
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
	out += CheckDirection(pTrans2->mPosition.x, pTrans1->mPosition.x - pColl1->Dim.x, pTrans1->mPosition.x + pColl1->Dim.x);
	out += CheckDirection(pTrans2->mPosition.y, pTrans1->mPosition.y - pColl1->Dim.y, pTrans1->mPosition.y + pColl1->Dim.y);

	return out;
}

void PhysicSystem::AABBvsSphere(EntityID pEntityID1, EntityID pEntityID2, CollisionComponent* pAABBColl, TransformComponent* pAABBTrans, CollisionComponent* pSphereColl, TransformComponent* pSphereTrans)
{
	float tSquareDistance = SquareDistToPoint(pAABBColl, pAABBTrans, pSphereColl, pSphereTrans);

	bool tCollide = tSquareDistance <= (pSphereColl->Dim.x * pSphereColl->Dim.x);

	if (tCollide)
	{
		vec2 tNormDir = vec3toVec2(pSphereTrans->mPrevPosition - pAABBTrans->mPrevPosition);
		tNormDir.x /= pAABBColl->Dim.x;
		tNormDir.y /= pAABBColl->Dim.y;
		//Collision on vertical side (left or right)

		//DEBUG
//#ifdef _DEBUG
//		cout << "Collision happened! ComponentID that collided:" << pEntityID1 << " and " << pEntityID2 << endl;
//#endif
		//END DEBUG
		
		

		if (abs(tNormDir.x) > abs(tNormDir.y))
		{
			if (ComponentTable::GetInstance()->HasComponent(pEntityID2, VelocityType))
			{
				VelocityComponent* tVel = GetComponent<VelocityComponent>(pEntityID2);


				if (GetComponent<LabelComponent>(pEntityID1)->mLabel == Label::Pad)
				{
					SphereVsSphere(pEntityID1, pEntityID2, pAABBColl, pAABBTrans, pSphereColl, pSphereTrans);
				}
				else
				{
					tVel->mDirection.x *= -1;
				}


				if (tNormDir.x > 0)
				{
					//save old position
					float tOldX = pSphereTrans->mPosition.x;

					//move the sphere to the edge of the box
					pSphereTrans->mPosition.x = pAABBTrans->mPosition.x + pAABBColl->Dim.x + pSphereColl->Dim.x;

					//move out with the difference from old and edge position out
					pSphereTrans->mPosition.x += pSphereTrans->mPosition.x - tOldX;
				}
				else
				{
					//save old position
					float tOldX = pSphereTrans->mPosition.x;

					//move the sphere to the edge of the box
					pSphereTrans->mPosition.x = pAABBTrans->mPosition.x - pAABBColl->Dim.x - pSphereColl->Dim.x;

					//move out with the difference from old and edge position out
					pSphereTrans->mPosition.x += pSphereTrans->mPosition.x - tOldX;
				}
				
				


				
				//pSphereTrans->mPosition = pSphereTrans->mPrevPosition;

				//if (ComponentTable::GetInstance()->HasComponent(pEntityID1, VelocityType))
				//{
				//	VelocityComponent* tVel2 = GetComponent<VelocityComponent>(pEntityID1);
				//	float tDot = tVel2->mDirection*tVel->mDirection;
				//	if (tDot > 0.0f)
				//	{
				//		//Force component
				//		ComponentTable::GetInstance()->AddComponent(pEntityID2, VelocityForceType);

				//		//need to check if already have force


				//		VelocityForceComponent* tVelForceComp = GetComponent<VelocityForceComponent>(pEntityID2);
				//		tVelForceComp->mEndValue = tVel->mSpeed;
				//		tVelForceComp->mType = ByValue;
				//		tVelForceComp->mIncrease = false;
				//		tVelForceComp->mAmount = -0.09f;

				//		//Increase speed
				//		tVel->mSpeed *= 2;
				//	}
				//}
			}

		}
		else
		{
			if (ComponentTable::GetInstance()->HasComponent(pEntityID2, VelocityType))
			{
				VelocityComponent* tVel = GetComponent<VelocityComponent>(pEntityID2);
				if (GetComponent<LabelComponent>(pEntityID1)->mLabel == Label::Pad)
				{
					SphereVsSphere(pEntityID1, pEntityID2, pAABBColl, pAABBTrans, pSphereColl, pSphereTrans);
				}
				else
				{
					tVel->mDirection.y *= -1;
				}

				if (tNormDir.y > 0)
				{
					//save old position
					float tOldY = pSphereTrans->mPosition.y;

					//move the sphere to the edge of the box
					pSphereTrans->mPosition.y = pAABBTrans->mPosition.y + pAABBColl->Dim.y + pSphereColl->Dim.x;

					//move out with the difference from old and edge position out
					pSphereTrans->mPosition.y += pSphereTrans->mPosition.y - tOldY;
				}
				else
				{
					//save old position
					float tOldY = pSphereTrans->mPosition.y;

					//move the sphere to the edge of the box
					pSphereTrans->mPosition.y = pAABBTrans->mPosition.y - pAABBColl->Dim.y - pSphereColl->Dim.x;

					//move out with the difference from old and edge position out
					pSphereTrans->mPosition.y += pSphereTrans->mPosition.y - tOldY;
				}
			}
		}

		//send sound event
		if (ComponentTable::GetInstance()->HasComponent(pEntityID1, SoundCollisionType))
		{
			unsigned int* tSoundIDptr = new unsigned int();
			*tSoundIDptr = GetComponent<SoundCollisionComponent>(pEntityID1)->SoundID;
			EventManager::Payload tPayload;
			tPayload["SoundID"] = tSoundIDptr;
			mEventManager->BroadcastEvent("Sound", tPayload);
		}
		if (ComponentTable::GetInstance()->HasComponent(pEntityID2, SoundCollisionType))
		{
			unsigned int* tSoundIDptr = new unsigned int();
			*tSoundIDptr = GetComponent<SoundCollisionComponent>(pEntityID2)->SoundID;
			EventManager::Payload tPayload;
			tPayload["SoundID"] = tSoundIDptr;
			mEventManager->BroadcastEvent("Sound", tPayload);
		}
		
		//remove block
		if (ComponentTable::GetInstance()->HasComponent(pEntityID1, LabelType))
		{
			LabelComponent* tLabel = GetComponent<LabelComponent>(pEntityID1);

			if (tLabel->mLabel == Label::Box)		//if AABB is label Box, we remove it
			{
				EntityManager::GetInstance()->RemoveEntity(pEntityID1);
			}
			else if (tLabel->mLabel == Label::BottomArea)		//if bottom area, we lose
			{
				//not sure if we need to send any specific data here
				std::unordered_map<string, void*> tPayLoad;
				EventManager::GetInstance()->BroadcastEvent("CollideWithBottom", tPayLoad);
			}
			else if (tLabel->mLabel == Label::GoalBlock)
			{
				//remove entity
				EntityManager::GetInstance()->RemoveEntity(pEntityID1);

				//send event
				std::unordered_map<string, void*> tPayLoad;
				EventManager::GetInstance()->BroadcastEvent("CollideWithGoalBlock", tPayLoad);
			}
		}
	}
}


void PhysicSystem::HandleCollision(EntityID pEntityID1, EntityID pEntityID2, CollisionComponent* pColl1, TransformComponent* pTrans1, CollisionComponent* pColl2, TransformComponent* pTrans2)
{
	if (pColl1->mType == CollisionGeo::AABB)
	{
		if (pColl2->mType == CollisionGeo::AABB)
		{
			AABBvsAABB(pEntityID1, pEntityID2, pColl1, pTrans1, pColl2, pTrans2);
		}
		else if (pColl2->mType == CollisionGeo::Sphere)
		{
			AABBvsSphere(pEntityID1, pEntityID2, pColl1, pTrans1, pColl2, pTrans2);
		}
	}
	else if (pColl1->mType == CollisionGeo::Sphere)
	{
		if (pColl2->mType == CollisionGeo::AABB)
		{
			AABBvsSphere(pEntityID2, pEntityID1, pColl2, pTrans2, pColl1, pTrans1);
		}
		else if (pColl2->mType == CollisionGeo::Sphere)
		{
			SphereVsSphere(pEntityID1, pEntityID2, pColl1, pTrans1, pColl2, pTrans2);
		}
	}
}

void PhysicSystem::Update(double pDeltaTime)
{
	EntityManager* tEntManager = tEntManager->GetInstance();
	ComponentTable* tCompTable = tCompTable->GetInstance();
	int tMaxEnt = tEntManager->GetLastEntity();

	//update position with force
	//for (int i = 0; i < tMaxEnt; i++)
	//{

	//	//Ensure that relevant components exist
	//	short tFlags = VelocityForceType | TransformType;
	//	if (tCompTable->HasComponent(i, tFlags))
	//	{
	//		TransformComponent* tTrans = GetComponent<TransformComponent>(i);
	//		VelocityForceComponent* tVelForce = GetComponent<VelocityForceComponent>(i);

	//		if (tVelForce->mType == ForceType::ByValue)
	//		{
	//			tTrans->mPosition += tTrans->mPosition.Normalize() * tVelForce->mAmount * (float)pDeltaTime;
	//		}
	//		else if (tVelForce->mType == ForceType::Percentage)
	//		{
	//			tTrans->mPosition = tTrans->mPosition * tVelForce->mAmount * (float)pDeltaTime;
	//		}

	//		//we don't set previous position to position here... should move this code into same loop
	//		

	//		//check if reached goal on the velocity
	//		

	//		//DEBUG
	//		if (GetComponent<LabelComponent>(i)->mLabel == Label::Pad)
	//			cout << "Position for pad is: " << tTrans->mPosition.x << " " << tTrans->mPosition.y << endl;
	//		//END DEBUG
	//	}
	//}


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

					//Handles everything about collision
					HandleCollision(i, k, tColl1, tTrans1, tColl2, tTrans2);

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