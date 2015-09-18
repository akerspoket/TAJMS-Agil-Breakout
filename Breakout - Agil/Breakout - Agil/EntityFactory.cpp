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
	}

	return tNewEntityID;
}