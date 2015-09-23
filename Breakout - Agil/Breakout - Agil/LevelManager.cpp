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


	//Med Textfil
	vector<string> mEntitiyVector;
	mEntitiyVector = TextFileReader::ReadTextFile("Entities/Pad.txt");
	string tBlueprintNamn = "";
	//string TestSomSatan = "";
	for (size_t i = 0; i < mEntitiyVector.size(); i++)
	{
		//TestSomSatan = mEntitiyVector[i];
		if (mEntitiyVector[i].compare("xEntity") == 0)
		{
			++i;
			tBlueprintNamn = mEntitiyVector[i];
		}
		else if (mEntitiyVector[i].compare("xTranform") == 0)
		{
			tBlueprint[TransformType] = tTrans;
		}
		else if (mEntitiyVector[i].compare("xMesh") == 0)
		{
			++i;
			//std::wstring name(L+mEntitiyVector[i]);
			//const wchar_t* szName = name.c_str();
			std::wstring widestr = std::wstring(mEntitiyVector[i].begin(), mEntitiyVector[i].end());
			const wchar_t* widecstr = widestr.c_str();
			tMesh->mMaterialID = tGraphicsInterFace->CreateTexture(widecstr);///Här ska vi byta textur!!
			
			////////Sen fixa meshen till objektet när objLoader e klar så borde denna fungera
			++i;
			const char * tConstChar = mEntitiyVector[i].c_str();
			tMesh->mMeshID = tGraphicsInterFace->CreateObject(tConstChar);
			tBlueprint[MeshType] = tMesh;
		}
		else if (mEntitiyVector[i].compare("xLabel"))
		{
			///////////Kolla vilken label det är i LabelComponent
		}
	}

	///ska skapa en BluePrint












	//set component values
	//we ignore this and use the initialization values for test
	//WARNINIG: We should call the graphic engine for loading a texture then
	//return the ID To meshComponent
	tLabel->mLabel = Label::Pad;
	tColl->Dim = vec2(0.5, 0.5);

	//////////////////////////////////////////add padda to blueprint
	
	//tBlueprint[TransformType] = tTrans;
	tMesh->mMaterialID = tGraphicsInterFace->CreateTexture(L"test2in1pic.dds");
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
	tMesh->mMaterialID = tGraphicsInterFace->CreateTexture(L"test2in1pic.dds");///Här ska vi byta textur!!
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
	tMesh->mMaterialID = tGraphicsInterFace->CreateTexture(L"test2in1pic.dds");//prov

	tBallBlueprint[TransformType] = tTrans;
	tBallBlueprint[MeshType] = tMesh;
	tBallBlueprint[LabelType] = tLabel;
	tBallBlueprint[VelocityType] = tVelocity;
	tBallBlueprint[CollisionType] = tColl;

	

	mEntityFactory->RegisterEntityTemplate("Ball", tBallBlueprint);


	/////////////////////////////////GOALBLOCK///////////////////
	EntityFactory::EntityBlueprint tGoalBlockBlueprint;

	//Component values might be silly and have to be altered later
	tTrans = new TransformComponent();
	tMesh = new MeshComponent();
	tVelocity = new VelocityComponent();
	tLabel = new LabelComponent();
	tLabel->mLabel = Label::GoalBlock;
	tMesh->mMaterialID = tGraphicsInterFace->CreateTexture(L"test2in1pic.dds");///Här ska vi byta textur!!
	tGoalBlockBlueprint[TransformType] = tTrans;
	tGoalBlockBlueprint[MeshType] = tMesh;
	tGoalBlockBlueprint[VelocityType] = tVelocity;
	tGoalBlockBlueprint[LabelType] = tLabel;
	mEntityFactory->RegisterEntityTemplate("GoalBlock", tBlockBlueprint);
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
	
	//GraphicsInterface* tGraphicsInterFace = GraphicsInterface::GetSingleton();
	//tGraphicsInterFace->CreateTexture(L"test2in1pic.dds");
	//tGraphicsInterFace->CreateObject("Box.obj");


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
	int t_forLoopI = mLevelTextVector.size();
	int t_forLooPJ = mLevelTextVector[2].size();
	for (size_t i = 0; i < t_forLoopI; i++)
	{
		for (size_t j = 0; j < t_forLooPJ; j++)
		{
			if (mLevelTextVector[i].at(j) == 'X')
			{
				tNewID = mEntityFactory->CreateEntity("Block");
				tTrans = GetComponent<TransformComponent>(tNewID);
				tTrans->mPosition.x = i;
				tTrans->mPosition.y = j;
			}
		}
	}



	
	/////////////////////BLOCKS//////////////////////
	//
	//int blockX = 10;
	//int blockY = 5;

	////Space between blocks. Should probably be expanded to account for block sizes
	////Hard-coded until we can read from proper level file
	//float margin = 1;

	//for (int i = 0; i < blockX; i++)
	//	for (int j = 0; j < blockY; j++)
	//	{
	//		tNewID = mEntityFactory->CreateEntity("Block");
	//		tTrans = GetComponent<TransformComponent>(tNewID);
	//		tTrans->mPosition.x = margin*i;
	//		tTrans->mPosition.y = margin*j; 
	//	}

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
	tNewID = mEntityFactory->CreateEntity("GoalBlock");
	GetComponent<TransformComponent>(tNewID)->mPosition = vec3(0, 0, 0);
	//ComponentTable::GetInstance()->AddComponent(tNewID, LabelType);
	//GetComponent<LabelComponent>(tNewID)->mLabel = Label::GoalBlock;


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
