#include "ShipGunSystem.h"
#include "EventManager.h"
#include "EntityManager.h"
#include "ComponentTable.h"
#include "StorageShelf.h"

#include "TransformComponent.h"
#include "LabelComponent.h"
#include "AttachedComponent.h"
#include "VelocityComponent.h"
#include "CollisionComponent.h"


ShipGunSystem::ShipGunSystem() {}
ShipGunSystem::ShipGunSystem(string pName) :System(pName)
{
	mCannonAngle = 3.1415 / 2;
	mCannonAngleFollowSpeed = 5;
	mCannonFollowSpeed = 22;
}
ShipGunSystem::~ShipGunSystem() {}
void ShipGunSystem::Initialize() {}
void ShipGunSystem::Start() {}
void ShipGunSystem::Update(double pDeltaTime)
{
	EntityManager* tEntManager = tEntManager->GetInstance();
	ComponentTable* tCompTable = tCompTable->GetInstance();
	int tMaxEnt = tEntManager->GetLastEntity();

	//Find the IDs so its easier to work with
	//WILL be messed up if we have more than one cannon, or more than one ball. 
	//Or, more interestingly, if we have a ball | cannon | pad
	EntityID tBallID = -1;
	EntityID tCannonID = -1;
	EntityID tPadID = -1;
	for (int i = 0; i < tMaxEnt; i++)
	{
		if (ComponentTable::GetInstance()->HasComponent(i, LabelType)
			&& GetComponent<LabelComponent>(i)->HasLabel(Ball))
			tBallID = i;
		if (ComponentTable::GetInstance()->HasComponent(i, LabelType)
			&& GetComponent<LabelComponent>(i)->HasLabel(Cannon))
			tCannonID = i;
		if (ComponentTable::GetInstance()->HasComponent(i, LabelType)
			&& GetComponent<LabelComponent>(i)->HasLabel(Pad))
			tPadID = i;
	}
	//Check so that the entities exist
	if (tBallID != -1 && tCannonID != -1 && tPadID != -1)
	{
		//Get direction angle relative y axis
		vec2 yAxis = vec2(0, -1);
		vec2 ballDir = vec3toVec2(GetComponent<VelocityComponent>(tBallID)->mDirection);
		if (ballDir.y < 0)
		{
			float dot = yAxis.x*ballDir.x + yAxis.y*ballDir.y;
			float det = yAxis.x*ballDir.y - yAxis.y*ballDir.x;
			float axisDirAngle = atan2(det, dot);

			//Calculate intersection point by multiplying movement direction with distance to intersection
			vec2 ballPos = vec3toVec2(GetComponent<TransformComponent>(tBallID)->mPosition);
			vec2 padPos = vec3toVec2(GetComponent<TransformComponent>(tPadID)->mPosition);
			vec2 padDims = GetComponent<CollisionComponent>(tPadID)->Dim;
			float ballHeightFromPad = ballPos.y - padPos.y - padDims.y;
			vec2 u = ballDir * abs((ballHeightFromPad * (1 / cos(axisDirAngle))));//Direction vector * length of hypotenuse
			vec2 ballIntersectPos = ballPos + u;

			vec2 padEdges = vec2((padPos.x - padDims.x), (padPos.x + padDims.x));

			//Check if intersect is on pad
			if (ballIntersectPos.x > padEdges.x && ballIntersectPos.x < padEdges.y)
			{
				//Fix cannon direction
				mBallIntersectPos.y = ballIntersectPos.y;
				//if (mBallIntersectPos.x > 
				vec3 tCannonDirection = CalculateCannonDirection(ballIntersectPos, vec2(0, 0), padPos);
				float angle = atan2(-1 * tCannonDirection.x, tCannonDirection.y) +3.1415 / 2;

				if (angle > mCannonAngle)
				{
					mCannonAngle += pDeltaTime*mCannonAngleFollowSpeed;
					if (angle < mCannonAngle)//we overshot
						mCannonAngle = angle;
				}
				else if (angle < mCannonAngle)
				{
					mCannonAngle -= pDeltaTime*mCannonAngleFollowSpeed;
					if (angle > mCannonAngle)//we overshot
						mCannonAngle = angle;
				}

				vec3 debugDirection = vec3(mCannonAngle, 0, 0);

				GetComponent<TransformComponent>(tCannonID)->mQuatRotation = vec3toVec4(debugDirection);
				
				//Fix cannon position
				//if (ballIntersectPos.x > padPos.x - padDims.x)
				//	ballIntersectPos.x = padPos.x - padDims.x;
				//else if (ballIntersectPos.x < padPos.x + padDims.x)
				//	ballIntersectPos.x = padPos.x + padDims.x;
				
				float pos = ballIntersectPos.x - padPos.x;

				if (pos > mCannonPos)
				{
					mCannonPos += pDeltaTime*mCannonFollowSpeed;
					if (pos < mCannonPos)//we overshot
						mCannonPos = pos;
				}
				else if (pos < mCannonAngle)
				{
					mCannonPos -= pDeltaTime*mCannonFollowSpeed;
					if (pos > mCannonPos)//we overshot
						mCannonPos = pos;
				}


				GetComponent<AttachedComponent>(tCannonID)->relPos.x = 1*mCannonPos;

				//GetComponent<AttachedComponent>(tCannonID)->relPos.x = ballIntersectPos.x - padPos.x;

			}
		}

		//vec3 tCannonDirection = (GetComponent<TransformComponent>(tBallID)->mPosition - GetComponent<TransformComponent>(tPadID)->mPosition).Normalized();
		//vec3 tCannonDirection = CalculateCannonDirection()
		//float angle = atan2(-1 * tCannonDirection.x, tCannonDirection.y);
		//vec3 debugDirection = vec3(angle+(3.1415/2), 0, 0);
		//GetComponent<TransformComponent>(tCannonID)->mQuatRotation = vec3toVec4(debugDirection);
	}

}
void ShipGunSystem::Pause() {}
void ShipGunSystem::Stop() {}
void ShipGunSystem::OnEvent(Event* pEvent) {}


vec3 ShipGunSystem::CalculateCannonDirection(vec2 ballIntersectPos, vec2 pBallPos, vec2 pPadPos)
{
		vec2 tPadSphereOffset = vec2(0, -5); //how large we want the sphere to be
		vec2 tPadSpherePos = pPadPos + tPadSphereOffset;
		vec2 collision = ballIntersectPos - tPadSpherePos;
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
	
		if (tDir.y < 0.4) //this hard coded value right here... READ mMinAngle IN PHYS SYSTEM!!
		{
			float tExitX = 1;
			if (tDir.x < 0)
				tExitX = -1;
			tDir = vec2(tExitX, 0.4).Normalize();
		}
	
		return vec2toVec3(tDir).Normalized();
}