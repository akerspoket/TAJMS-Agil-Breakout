#include "EntityFactory.h"
#include "EntityManager.h"
#include "ComponentTable.h"
#include "PhysicComponent.h"
#include "TransformComponent.h"


EntityFactory::EntityFactory()
{
}


EntityFactory::~EntityFactory()
{
}


void EntityFactory::Initialize()
{
	//EntityManager* tEntityManager = tEntityManager->GetInstance();
	//ComponentTable* tComponentTable = tComponentTable->GetInstance();

	//EntityID tNewID = tEntityManager->AddEntity();

	////we want to add physic compnent
	//PhysicComponent* tPhysicComp = new PhysicComponent();
	//tPhysicComp->mIsSphere = true;

	//TransformComponent* tTransComp = new TransformComponent();
	//
	//tTransComp->mPosition[0] = 0.0f;
	//tTransComp->mPosition[1] = 0.0f;
	//tTransComp->mPosition[2] = 0.0f;

	//tTransComp->mRotation[0] = 0.0f;
	//tTransComp->mRotation[1] = 0.0f;
	//tTransComp->mRotation[2] = 0.0f;

	//std::vector<Component*> tCompArray;
	//tCompArray.resize(NUM_OF_COMOPNENTS);

	//tCompArray[PhysicType] = tPhysicComp;
	//tCompArray[TransformType] = tTransComp;

	//mMap["Boll"] = tCompArray;
	
}

EntityID EntityFactory::CreateEntity(std::string pTemplateName)
{
	return 0;
}