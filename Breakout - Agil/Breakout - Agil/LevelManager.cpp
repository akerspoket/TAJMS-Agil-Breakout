#include "LevelManager.h"
#include "StorageShelf.h"
#include "TransformComponent.h"
#include "MeshComponent.h"
#include "LabelComponent.h"
#include "PhysicComponent.h"
#include "VelocityComponent.h"




LevelManager* LevelManager::mSingleton = nullptr;

LevelManager* LevelManager::GetInstance()
{
	if (mSingleton == nullptr)
	{
		mSingleton = new LevelManager();
	}

	return mSingleton;
}

LevelManager::LevelManager()
{
	mEntityFactory = mEntityFactory->GetInstance();
}


LevelManager::~LevelManager()
{
}

void LevelManager::Initialize()
{
	//TODO: TEST remove this when we load maps in a good way
	EntityFactory::EntityBlueprint tBlueprint;

	TransformComponent* tTrans = new TransformComponent();
	MeshComponent* tMesh = new MeshComponent();
	LabelComponent* tLabel = new LabelComponent();
	PhysicComponent* tPhysic = new PhysicComponent();
	VelocityComponent* tVelocity = new VelocityComponent();

	//set component values
	//we ignore this and use the initialization values for test
	//WARNINIG: We should call the graphic engine for loading a texture then
	//return the ID To meshComponent
	tLabel->mLabel = Label::Pad;

	//add to blueprint
	tBlueprint[TransformType] = tTrans;
	tBlueprint[MeshType] = tMesh;
	tBlueprint[LabelType] = tLabel;

	mEntityFactory->RegisterEntityTemplate("Padda", tBlueprint);
}

void LevelManager::GenerateWorld(string pWorldName)
{
	EntityID tNewID = mEntityFactory->CreateEntity("Padda");
	TransformComponent* tTrans = GetComponent<TransformComponent>(tNewID);

	tTrans->mPosition[0] = 1.0f;
}
