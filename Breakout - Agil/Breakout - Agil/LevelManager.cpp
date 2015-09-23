#include "LevelManager.h"
#include "StorageShelf.h"
#include "TransformComponent.h"
#include "MeshComponent.h"
#include "LabelComponent.h"
#include "PhysicComponent.h"
#include "VelocityComponent.h"
#include "CollisionComponent.h"
#include "TextFileReader.h"
#include "ComponentTable.h"
#include <iostream>
#include "GraphicsInterface.h"
using namespace std;



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
void LevelManager::AnalyzeText(string pTextToCheck)
{

}

void LevelManager::Initialize()
{
	GraphicsInterface* tGraphicsInterFace = GraphicsInterface::GetSingleton();
	//TODO: TEST remove this when we load maps in a good way

	/////////////PADDA///////////////
	EntityFactory::EntityBlueprint tBlueprint;

	TransformComponent* tTrans = new TransformComponent();
	MeshComponent* tMesh = new MeshComponent();
	LabelComponent* tLabel = new LabelComponent();
	PhysicComponent* tPhysic = new PhysicComponent();
	VelocityComponent* tVelocity = new VelocityComponent();
	CollisionComponent* tColl = new CollisionComponent();



	///ska skapa en BluePrint


	////Med Textfil
	//vector<string> mEntitiyVector;
	//mEntitiyVector = TextFileReader::ReadTextFile("Entities/Pad.txt");
	//string tBlueprintNamn = "";
	//string TestSomSatan = "";
	//for (size_t i = 0; i < mEntitiyVector.size(); i++)
	//{
	//	//TestSomSatan = mEntitiyVector[i];
	//	if (mEntitiyVector[i].compare("xEntity") == 0)
	//	{
	//		++i;
	//		tBlueprintNamn = mEntitiyVector[i];
	//	}
	//	else if (mEntitiyVector[i].compare("xTranform") == 0)
	//	{
	//		tBlueprint[TransformType] = tTrans;
	//	}
	//	else if (mEntitiyVector[i].compare("xMesh") == 0)
	//	{
	//		//++i;
	//		//std::wstring name((L)mEntitiyVector[i]);
	//		//const wchar_t* szName = name.c_str();
	//		//
	//		//tGraphicsInterFace->CreateTexture(mEntitiyVector[i]);
	//		//++i;
	//		//tGraphicsInterFace->CreateObject(mEntitiyVector[i]);
	//		////tBlueprint[MeshType] = mEntitiyVector[i];
	//	}
	//	else if (mEntitiyVector[i].compare("xLabel"))
	//	{
	//		///////////Kolla vilken label det är i LabelComponent

	//	}
	//}












	//set component values
	//we ignore this and use the initialization values for test
	//WARNINIG: We should call the graphic engine for loading a texture then
	//return the ID To meshComponent
	tLabel->mLabel = Label::Pad;
	tColl->Dim = vec2(0.5, 0.5);
	
	//add to blueprint
	
	//tBlueprint[TransformType] = tTrans;
	tBlueprint[MeshType] = tMesh;
	tBlueprint[LabelType] = tLabel;
	tBlueprint[CollisionType] = tColl;

	mEntityFactory->RegisterEntityTemplate("Padda", tBlueprint);

	/////////////////////////////////BLOCK///////////////////
	EntityFactory::EntityBlueprint tBlockBlueprint;

	//Component values might be silly and have to be altered later
	tTrans = new TransformComponent();
	tMesh = new MeshComponent();
	tVelocity = new VelocityComponent();
	tBlockBlueprint[TransformType] = tTrans;
	tBlockBlueprint[MeshType] = tMesh;
	tBlockBlueprint[VelocityType] = tVelocity;



	mEntityFactory->RegisterEntityTemplate("Block", tBlockBlueprint);

	///////////////////////////BALL////////////////////////
	EntityFactory::EntityBlueprint tBallBlueprint;

	//Component values might be silly and have to be altered later
	tTrans = new TransformComponent();
	tMesh = new MeshComponent();
	tLabel = new LabelComponent();
	tVelocity = new VelocityComponent();
	tColl = new CollisionComponent();

	//We set the label here since it never changes
	tLabel->mLabel = Label::Ball;

	tColl->mType = CollisionGeo::Sphere;
	tColl->Dim.x = 0.2f;

	tBallBlueprint[TransformType] = tTrans;
	tBallBlueprint[MeshType] = tMesh;
	tBallBlueprint[LabelType] = tLabel;
	tBallBlueprint[VelocityType] = tVelocity;
	tBallBlueprint[CollisionType] = tColl;

	

	mEntityFactory->RegisterEntityTemplate("Ball", tBallBlueprint);

	////////////////////SIDE WALL///////////////////////////
	EntityFactory::EntityBlueprint tWallBlueprint;

	tTrans = new TransformComponent();
	tColl = new CollisionComponent();
	tColl->mType = CollisionGeo::AABB;
	tColl->Dim = vec2(30,0.2f);
	
	tWallBlueprint[TransformType] = tTrans;
	tWallBlueprint[CollisionType] = tColl;

	mEntityFactory->RegisterEntityTemplate("HorWall", tWallBlueprint);

	///////////////////TOP-BOT WALL////////////////
	EntityFactory::EntityBlueprint tWall2Blueprint;

	tTrans = new TransformComponent();
	tColl = new CollisionComponent();
	tColl->mType = CollisionGeo::AABB;
	tColl->Dim = vec2(0.2f, 30.0f);

	tWall2Blueprint[TransformType] = tTrans;
	tWall2Blueprint[CollisionType] = tColl;

	mEntityFactory->RegisterEntityTemplate("VerWall", tWall2Blueprint);

}

void LevelManager::GenerateWorld(string pWorldName)
{
	
	//tGraphicsInterFace->CreateTexture(L"namn.dds");
	//tGraphicsInterFace->CreateObject("Box.obj");


	////////////////////PADDA//////////////////
	EntityID tNewID = mEntityFactory->CreateEntity("Padda");
	TransformComponent* tTrans = GetComponent<TransformComponent>(tNewID);
	tTrans->mPosition = vec3(0, -3, 8);
	int derp = GetComponent<LabelComponent>(tNewID)->mLabel;
	GetComponent<VelocityComponent>(tNewID)->mSpeed = 0.001f;
	
	//Reading The level from textfile
	vector<string> mLevelTextVector;
	mLevelTextVector = TextFileReader::ReadTextFile(pWorldName);
	string hej = "12345";
	string hejsan;

	for (size_t i = 0; i < mLevelTextVector[7].size(); i++)
	{
		hejsan+= mLevelTextVector[5].at(i);
	}



	/////////////////////BLOCKS//////////////////////

	
	int blockX = 4;
	int blockY = 3;
	vec2 startOffset = vec2(-2, 0);

	//Space between blocks. Should probably be expanded to account for block sizes
	//Hard-coded until we can read from proper level file
	float margin = 1.5;

	for (int i = 0; i < blockX; i++)
		for (int j = 0; j < blockY; j++)
		{
			tNewID = mEntityFactory->CreateEntity("Block");
			tTrans = GetComponent<TransformComponent>(tNewID);
			tTrans->mPosition.x = margin*i+startOffset.x;
			tTrans->mPosition.y = margin*j+startOffset.y;
		}

	//////////////////////////BALL////////////////////
	float tStartPositionX = 2;
	float tStartPositionY = 2;

	tNewID = mEntityFactory->CreateEntity("Ball");
	tTrans = GetComponent<TransformComponent>(tNewID);
	tTrans->mPosition.x = tStartPositionX;
	tTrans->mPosition.y = tStartPositionY;

	VelocityComponent* tVel = GetComponent<VelocityComponent>(tNewID);
	tVel->mSpeed = 0.001f;
	vec3 tStartDirection = vec3(-1.0f, 1.0f, 0.0f).Normalize();
	tVel->mDirection.x = tStartDirection.x;
	tVel->mDirection.y = tStartDirection.y;
	tVel->mDirection.z = tStartDirection.z;


	////////////////////GOAL//////////////////////////
	tNewID = mEntityFactory->CreateEntity("Block");
	ComponentTable::GetInstance()->AddComponent(tNewID, LabelType);
	GetComponent<LabelComponent>(tNewID)->mLabel = Label::Goal;


	//////////////////TOP BOT WALL///////////////////
	tNewID = mEntityFactory->CreateEntity("HorWall");
	GetComponent<TransformComponent>(tNewID)->mPosition = vec3(0,4,8);

	tNewID = mEntityFactory->CreateEntity("HorWall");
	GetComponent<TransformComponent>(tNewID)->mPosition = vec3(0, -4, 8);

	/////////////////SIDE WALLS/////////////////////////
	tNewID = mEntityFactory->CreateEntity("VerWall");
	GetComponent<TransformComponent>(tNewID)->mPosition = vec3(4, 0, 8);

	tNewID = mEntityFactory->CreateEntity("VerWall");
	GetComponent<TransformComponent>(tNewID)->mPosition = vec3(-4, 0, 8);
}