#include "EntityFactory.h"
#include "EntityManager.h"
#include "ComponentTable.h"
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

void EntityFactory::RegisterEntityTemplate(map<string, vector<string>> pEntityString)
{
	string tName = "";
	EntityBlueprint* tEntityBlueprint = new EntityBlueprint();
	


	for (map<string, vector<string>>::iterator iter = pEntityString.begin(); iter != pEntityString.end(); ++iter)
	{
		if (iter->first == "Name")
		{
			if (iter->second.size() == 1)
			{
				tName = iter->second[0];
			}
		}
		else if (iter->first == "TransformCompnent")
		{
			TransformComponent* tNewComp = new TransformComponent();
			if (iter->second.size() == 6)
			{
				tNewComp->mPosition[0] = stof(iter->second.at(0));
				tNewComp->mPosition[1] = stof(iter->second.at(1));
				tNewComp->mPosition[2] = stof(iter->second.at(2));

				tNewComp->mRotation[0] = stof(iter->second.at(3));
				tNewComp->mRotation[1] = stof(iter->second.at(4));
				tNewComp->mRotation[2] = stof(iter->second.at(5));
			}
			tEntityBlueprint->at(TransformType) = tNewComp;
		}
		else if (iter->first == "PhysicComponent")
		{
			PhysicComponent* tNewComp = new PhysicComponent();
			if (iter->second.size() == 1)
			{
				if (iter->second.at(0) == "1")
				{
					tNewComp->mIsSphere = true;
				}
				else
				{
					tNewComp->mIsSphere = false;
				}
			}
			tEntityBlueprint->at(PhysicType) = tNewComp;
		}
	}

	mEntityBlueprints[tName] = tEntityBlueprint;
}

EntityID EntityFactory::CreateEntity(std::string pTemplateName)
{
	//EntityManager* tEntityManager = tEntityManager->GetInstance();
	//EntityID tNewID = tEntityManager->AddEntity();
	//EntityBlueprint* tEntityBlueprint = mEntityBlueprints[pTemplateName];

	//for (std::map<ComponentType, void*>::iterator iter = tEntityBlueprint->begin(); iter != tEntityBlueprint->end(); ++iter)
	//{
	//	if (iter->first == ComponentType::TransformType)
	//	{
	//		
	//	}
	//	else if (iter->first == ComponentType::PhysicType)
	//	{

	//	}
	//}

	return 0;
}