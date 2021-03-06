#include "EntityFactory.h"
#include "EntityManager.h"
#include "ComponentTable.h"
#include "StorageShelf.h"
#include "PhysicComponent.h"
#include "TransformComponent.h"
#include "MeshComponent.h"
#include "LabelComponent.h"
#include "VelocityComponent.h"
#include "CollisionComponent.h"
#include "VelocityForceComponent.h"
#include "SoundCollisionComponent.h"
#include "AttachedComponent.h"
#include "ScoreValueComponent.h"
#include "MenyButtonComponent.h"
#include "PowerUpComponent.h"
#include "PowerUpContainComponent.h"
#include "EmitterComponent.h"

#include <string.h> //needed for linux


EntityFactory* EntityFactory::mSingleton = nullptr;

EntityFactory* EntityFactory::GetInstance()
{
	if (mSingleton == nullptr)
	{
		mSingleton = new EntityFactory();
	}
	return mSingleton;
}

EntityFactory::EntityFactory()
{
}


EntityFactory::~EntityFactory()
{
}


void EntityFactory::Initialize()
{
	
}

void EntityFactory::RegisterEntityTemplate(string pName, EntityBlueprint pComponents)
{
	string tName = pName;

	mEntityBlueprints[pName] = pComponents;
}

EntityID EntityFactory::CreateEntity(std::string pTemplateName)
{
	EntityBlueprint tComponentMap = mEntityBlueprints[pTemplateName];
	EntityManager* tEntityManager = tEntityManager->GetInstance();
	ComponentTable* tComponentTable = tComponentTable->GetInstance();

	//create a new ID
	EntityID tNewEntityID = tEntityManager->AddEntity();

	//copy components
	for (EntityBlueprint::iterator iter = tComponentMap.begin(); iter != tComponentMap.end(); ++iter)
	{
		tComponentTable->AddComponent(tNewEntityID, iter->first);

		if (iter->first == ComponentType::PhysicType)
		{
			memcpy(GetComponent<PhysicComponent>(tNewEntityID), iter->second, sizeof(PhysicComponent));
		}
		else if (iter->first == ComponentType::TransformType)
		{
			memcpy(GetComponent<TransformComponent>(tNewEntityID), iter->second, sizeof(TransformComponent));
		}
		else if (iter->first == ComponentType::MeshType)
		{
			memcpy(GetComponent<MeshComponent>(tNewEntityID), iter->second, sizeof(MeshComponent));
		}
		else if (iter->first == ComponentType::LabelType)
		{
			memcpy(GetComponent<LabelComponent>(tNewEntityID), iter->second, sizeof(LabelComponent));
		}
		else if (iter->first == ComponentType::VelocityType)
		{
			memcpy(GetComponent<VelocityComponent>(tNewEntityID), iter->second, sizeof(VelocityComponent));
		}
		else if (iter->first == ComponentType::CollisionType)
		{
			memcpy(GetComponent<CollisionComponent>(tNewEntityID), iter->second, sizeof(CollisionComponent));
		}
		else if (iter->first == ComponentType::VelocityForceType)
		{
			memcpy(GetComponent<VelocityForceComponent>(tNewEntityID), iter->second, sizeof(VelocityForceComponent));
		}
		else if (iter->first == ComponentType::SoundCollisionType)
		{
			memcpy(GetComponent<SoundCollisionComponent>(tNewEntityID), iter->second, sizeof(SoundCollisionComponent));
		}
		else if (iter->first == ComponentType::AttachedType)
		{
			memcpy(GetComponent<AttachedComponent>(tNewEntityID), iter->second, sizeof(AttachedComponent));
		}
		else if (iter->first == ComponentType::ScoreValueType)
		{
			memcpy(GetComponent<ScoreValueComponent>(tNewEntityID), iter->second, sizeof(ScoreValueComponent));
		}
		else if (iter->first == ComponentType::MenyButtonType)
		{
			memcpy(GetComponent<MenyButtonComponent>(tNewEntityID), iter->second, sizeof(MenyButtonComponent));
		}
		else if (iter->first == ComponentType::PowerUpType)
		{
			memcpy(GetComponent<PowerUpComponent>(tNewEntityID), iter->second, sizeof(PowerUpComponent));
		}
		else if (iter->first == ComponentType::PowerUpContainType)
		{
			memcpy(GetComponent<PowerUpContainComponenet>(tNewEntityID), iter->second, sizeof(PowerUpContainComponenet));
		}
		else if (iter->first == ComponentType::EmitterType)
		{
			memcpy(GetComponent<EmitterComponent>(tNewEntityID), iter->second, sizeof(EmitterComponent));
		}


	}

	return tNewEntityID;
}