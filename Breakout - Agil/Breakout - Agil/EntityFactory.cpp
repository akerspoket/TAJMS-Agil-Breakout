#include "EntityFactory.h"
#include "EntityManager.h"
#include "ComponentTable.h"
#include "StorageShelf.h"
#include "PhysicComponent.h"
#include "TransformComponent.h"



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
	}

	return tNewEntityID;
}