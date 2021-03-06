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
#include "GameState.h"
#include "PowerUpComponent.h"
#include "ScoreValueComponent.h"
#include <cmath> //needed for linux... come on!


PhysicSystem::PhysicSystem()
{

}

PhysicSystem::PhysicSystem(string pName) :System(pName)
{

}

PhysicSystem::~PhysicSystem()
{

}

void PhysicSystem::Initialize()
{
	mEventManager = mEventManager->GetInstance();
	mEventManager->Subscribe("DebugTest", this);

	mMinAngle = 0.4;
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

}

void PhysicSystem::SphereVsSphere(EntityID pEntityID1, EntityID pEntityID2, CollisionComponent* pColl1, TransformComponent* pTrans1, CollisionComponent* pColl2, TransformComponent* pTrans2)
{
	float tLength = (pTrans1->mPosition - pTrans2->mPosition).Abs();

	float tSumRadius = pColl1->Dim.x + pColl2->Dim.x;

	//check if distance between points is less then sumradius
	bool rCollided = tLength < tSumRadius;

	if (rCollided)
	{
		//Special case if component is ball and collids with the pad
		if (GetComponent<LabelComponent>(pEntityID2)->HasLabel(Label::Ball) && !ComponentTable::GetInstance()->HasComponent(pEntityID1, PowerUpContainType))
		{
			VelocityComponent* ballVel = GetComponent<VelocityComponent>(pEntityID2);
			vec2 tPadSphereOffset = vec2(0, -5); //how large we want the sphere to be
			vec2 tBallPos = vec3toVec2(pTrans2->mPosition);
			vec2 tPadSpherePos = vec3toVec2(pTrans1->mPosition) + tPadSphereOffset;
			vec2 collision = tBallPos - tPadSpherePos;
			float distance = collision.Abs();

			collision = collision * (1 / distance);
			//vec2 tDir = vec3toVec2(ballVel->mDirection); //physically correct thingy
			vec2 tDir = vec2(0, -1); //gameplay thingy
			float aci = tDir*collision;
			float bci = 0;

			float acf = bci;
			float bcf = aci;

			tDir += collision*(0 - aci);
			tDir -= collision*(bcf - 0);

			if (tDir.y < mMinAngle) //exit angle too low
			{
				float tExitX = 1;
				if (tDir.x < 0)
					tExitX = -1;
				tDir = vec2(tExitX, mMinAngle).Normalize();
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
bool PhysicSystem::ExplosiveCollisionCheck(CollisionComponent* pColSphere, TransformComponent* pTransSphere, CollisionComponent* pColAABB, TransformComponent* pTransAABB)
{
	float tSquareDistance = SquareDistToPoint(pColAABB, pTransAABB, pColSphere, pTransSphere);
	bool tCollide = tSquareDistance <= (pColSphere->Dim.x * pColSphere->Dim.x);

	if (tCollide)
	{
		return true;
	}

	return false;
}
void PhysicSystem::AABBvsSphere(EntityID pEntityID1, EntityID pEntityID2, CollisionComponent* pAABBColl, TransformComponent* pAABBTrans, CollisionComponent* pSphereColl, TransformComponent* pSphereTrans)
{
	float tSquareDistance = SquareDistToPoint(pAABBColl, pAABBTrans, pSphereColl, pSphereTrans);

	bool tCollide = tSquareDistance <= (pSphereColl->Dim.x * pSphereColl->Dim.x);
	float  hejsan = (pSphereColl->Dim.x * pSphereColl->Dim.x);
	EntityID aabbID = pEntityID1;
	EntityID sphereID = pEntityID2;

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

		//Pad picks up powerup
		if (ComponentTable::GetInstance()->HasComponent(sphereID, PowerUpContainType)
			&& ComponentTable::GetInstance()->HasComponent(aabbID, LabelType)
			&& GetComponent<LabelComponent>(aabbID)->HasLabel(Pad))
		{
			unordered_map<string, void*> pupPayload;
			EntityID* entID = new EntityID();
			*entID = aabbID;
			pupPayload["EntityID"] = entID;
			EntityID* pupID = new EntityID();
			*pupID = sphereID;
			pupPayload["PupEntityID"] = pupID;
			EventManager::GetInstance()->BroadcastEvent("PowerUpPickedUp", pupPayload);

			EntityManager::GetInstance()->RemoveEntity(sphereID);

		}

		//for powerups test
		if (ComponentTable::GetInstance()->HasComponent(sphereID, LabelType) && GetComponent<LabelComponent>(sphereID)->HasLabel(PowerUpDown))
		{
			if (GetComponent<LabelComponent>(aabbID)->HasLabel(Wall) && !GetComponent<LabelComponent>(aabbID)->HasLabel(BottomArea))
			{
				VelocityComponent* tVel = GetComponent<VelocityComponent>(pEntityID2);

				if (abs(tNormDir.x) > abs(tNormDir.y))
				{
					tVel->mDirection.x *= -1;
				}
				else
				{
					tVel->mDirection.y *= -1;
				}
			}
		}


		//Ball collides with AABB
		if (ComponentTable::GetInstance()->HasComponent(sphereID, LabelType) && GetComponent<LabelComponent>(sphereID)->HasLabel(Ball) )
		{

			if (abs(tNormDir.x) > abs(tNormDir.y))
			{
				if (ComponentTable::GetInstance()->HasComponent(pEntityID2, VelocityType))
				{
					VelocityComponent* tVel = GetComponent<VelocityComponent>(pEntityID2);


					if (GetComponent<LabelComponent>(pEntityID1)->HasLabel(Pad))
					{
						SphereVsSphere(pEntityID1, pEntityID2, pAABBColl, pAABBTrans, pSphereColl, pSphereTrans);
					}
					else if (!(ComponentTable::GetInstance()->HasComponent(sphereID, PowerUpType) && GetComponent<PowerUpComponent>(sphereID)->HasPowerUp(Piercing) && !GetComponent<LabelComponent>(aabbID)->HasLabel(Wall)))	//if not powerupPierce and a wall
					{
						tVel->mDirection.x *= -1;
					}

					if (GetComponent<LabelComponent>(pEntityID1)->HasLabel(Pad))
					{
						pSphereTrans->mPosition.y = pAABBTrans->mPosition.y + pAABBColl->Dim.y + pSphereColl->Dim.x;
						//tVel->mDirection.y = mMinAngle;
						//tVel->mDirection.x = (tVel->mDirection.x > 0) - (tVel->mDirection.x < 0);
						//tVel->mDirection.Normalize();
					}


					if (!(ComponentTable::GetInstance()->HasComponent(sphereID, PowerUpType) && GetComponent<PowerUpComponent>(sphereID)->HasPowerUp(Piercing) && !GetComponent<LabelComponent>(aabbID)->HasLabel(Wall)))
					{
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
					}

				}
			}
			else
			{
				if (ComponentTable::GetInstance()->HasComponent(pEntityID2, VelocityType))
				{
					VelocityComponent* tVel = GetComponent<VelocityComponent>(pEntityID2);
					if (GetComponent<LabelComponent>(pEntityID1)->HasLabel(Pad))
					{
						SphereVsSphere(pEntityID1, pEntityID2, pAABBColl, pAABBTrans, pSphereColl, pSphereTrans);
					}
					else if (!(ComponentTable::GetInstance()->HasComponent(sphereID, PowerUpType) && GetComponent<PowerUpComponent>(sphereID)->HasPowerUp(Piercing) && !GetComponent<LabelComponent>(aabbID)->HasLabel(Wall)))	//if not powerupPierce and a wall
					{
						tVel->mDirection.y *= -1;
					}
					if (!(ComponentTable::GetInstance()->HasComponent(sphereID, PowerUpType) && GetComponent<PowerUpComponent>(sphereID)->HasPowerUp(Piercing) && !GetComponent<LabelComponent>(aabbID)->HasLabel(Wall)))
					{
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
			}


			//Broadcast that there was a collision
			unordered_map<string, void*> payload;
			EntityID* id1 = new EntityID();
			*id1 = pEntityID1;
			payload["ID1"] = id1;
			EntityID* id2 = new EntityID();
			*id2 = pEntityID2;
			payload["ID2"] = id2;
			mEventManager->BroadcastEvent("Collision", payload);
		}
		//remove block
		if (ComponentTable::GetInstance()->HasComponent(sphereID, LabelType) &&
			GetComponent<LabelComponent>(sphereID)->HasLabel(Ball))
		{
			if (ComponentTable::GetInstance()->HasComponent(pEntityID1, LabelType))
			{
				LabelComponent* tLabel = GetComponent<LabelComponent>(pEntityID1);

				if (tLabel->HasLabel(Box))		//if AABB is label Box, we remove it
				{

					if (ComponentTable::GetInstance()->HasComponent(pEntityID1, PowerUpContainType))
					{
						unordered_map<string, void*> payload;
						EntityID* entID = new EntityID();
						vec3* direction = new vec3();
						float* speed = new float();
						*entID = pEntityID1;
						*direction = vec3(0, -1, 0);
						*speed = 5;
						payload["EntityID"] = entID;
						payload["direction"] = direction;
						payload["speed"] = speed;
						EventManager::GetInstance()->BroadcastEvent("SpawnPowerUp", payload);
					}
					EntityManager::GetInstance()->RemoveEntity(pEntityID1);
				}
				else if (tLabel->HasLabel(BottomArea))		//if bottom area, we lose
				{
					//not sure if we need to send any specific data here
					std::unordered_map<string, void*> tPayLoad;
					if (GetComponent<LabelComponent>(pEntityID2)->HasLabel(Ball))
						EventManager::GetInstance()->BroadcastEvent("CollideWithBottom", tPayLoad);
				}
				else if (tLabel->HasLabel(GoalBlock))
				{
					//remove entity

	

					//send event
					std::unordered_map<string, void*> tPayLoad;
					EventManager::GetInstance()->BroadcastEvent("CollideWithGoalBlock", tPayLoad);
					EntityManager::GetInstance()->RemoveEntity(pEntityID1);
				}
			}
		}
		//short pupType = GetComponent<PowerUpComponent>(sphereID)->powerUps;

		if (ComponentTable::GetInstance()->HasComponent(sphereID, PowerUpType) && GetComponent<PowerUpComponent>(sphereID)->HasPowerUp(FireBall) 
			&& !GetComponent<LabelComponent>(aabbID)->HasLabel(Wall))
		{
			EntityManager* tEntManager = tEntManager->GetInstance();
			ComponentTable* tCompTable = tCompTable->GetInstance();
			int tMaxEnt = tEntManager->GetLastEntity();
			bool tDidItCollide = false;
			int tRemoveScore = 0;
			//	for (int i = 0; i < tMaxEnt; i++)//
			//{//
			//CollisionComponent* tColl1 = GetComponent<CollisionComponent>(sphereID);
			GetComponent<CollisionComponent>(sphereID)->Dim.x *= 10;
			GetComponent<CollisionComponent>(sphereID)->Dim.y *= 10;
			CollisionComponent* tColl1 = GetComponent<CollisionComponent>(sphereID);
			TransformComponent* tTrans1 = GetComponent<TransformComponent>(sphereID);

			//if (tCompTable->HasComponent(sphereID, CollisionType | TransformType | LabelType) && GetComponent<LabelComponent>(i)->HasLabel(Ball))
			//	{	

			for (int k = 0; k < tMaxEnt; k++)
			{
				if (tCompTable->HasComponent(k, CollisionType | TransformType | LabelType) && (GetComponent<LabelComponent>(k)->HasLabel(Box) || GetComponent<LabelComponent>(k)->HasLabel(GoalBlock)))
				{
					//if (GetComponent<LabelComponent>(k)->HasLabel(Box) && GetComponent<LabelComponent>(k)->HasLabel(Waveable))
					//{
					//	int hejsan = 0;
					//}
					CollisionComponent* tColl2 = GetComponent<CollisionComponent>(k);
					TransformComponent* tTrans2 = GetComponent<TransformComponent>(k);

					//Handles everything about collision
					if (ExplosiveCollisionCheck(tColl1, tTrans1, tColl2, tTrans2))
					{
						tDidItCollide = false;
						if (GetComponent<LabelComponent>(k)->HasLabel(Box))		//if AABB is label Box, we remove it
						{

							if (ComponentTable::GetInstance()->HasComponent(k, PowerUpContainType))
							{
								unordered_map<string, void*> payload;
								EntityID* entID = new EntityID();
								vec3* direction = new vec3();
								float* speed = new float();
								*entID = k;
								*direction = vec3(0, -1, 0);
								*speed = 5;
								payload["EntityID"] = entID;
								payload["direction"] = direction;
								payload["speed"] = speed;
								EventManager::GetInstance()->BroadcastEvent("SpawnPowerUp", payload);
							}
							//send event
							//Broadcast that there was a collision
							tRemoveScore += GetComponent<ScoreValueComponent>(k)->value;

							EntityManager::GetInstance()->RemoveEntity(k);
						}
						else if (GetComponent<LabelComponent>(k)->HasLabel(GoalBlock))
						{
							//remove entity

							

							//send event
							std::unordered_map<string, void*> tPayLoad;
							EventManager::GetInstance()->BroadcastEvent("CollideWithGoalBlock", tPayLoad);

							EntityManager::GetInstance()->RemoveEntity(k);
						}
					}
				}
			}
			//}
			//}//
			//s�tta tillbaks dimensions
			GetComponent<CollisionComponent>(sphereID)->Dim.x /= 10;
			GetComponent<CollisionComponent>(sphereID)->Dim.y /= 10;
			//4123!!!
			if (tRemoveScore != 0)
			{
				
				unordered_map<string, void*> payload;
				EntityID* SphereID = new EntityID();
				*SphereID = sphereID;
				payload["SPHEREID"] = SphereID;
				mEventManager->BroadcastEvent("FireBallSound", payload);
				unordered_map<string, void*> payload1;
				int* ScoreToRemove = new int();
				*ScoreToRemove = tRemoveScore;
				payload1["ScoreToRemove"] = ScoreToRemove;
				mEventManager->BroadcastEvent("RemoveScore", payload1);
				
				
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

	switch (GameStateClass::GetInstance()->GetGameState())
	{
	case MenuScreen:
		break;
	case GameScreen:
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
		break;
	case DeathScreen:
		break;
	case PauseScreen:
		break;
	default:
		break;
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