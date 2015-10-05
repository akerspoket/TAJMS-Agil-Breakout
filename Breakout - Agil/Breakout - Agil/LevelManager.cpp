#include "LevelManager.h"
#include "EventManager.h"
#include "EntityManager.h"
#include "StorageShelf.h"
#include "TransformComponent.h"
#include "MeshComponent.h"
#include "LabelComponent.h"
#include "PhysicComponent.h"
#include "VelocityComponent.h"
#include "CollisionComponent.h"
#include "AttachedComponent.h"
#include "SoundCollisionComponent.h"
#include "TextFileReader.h"
#include "ComponentTable.h"
#include <iostream>
#include "GraphicsInterface.h"
#include "ScoreValueComponent.h"

#include "SoundEngine.h"
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
	

	TransformComponent* tTrans = new TransformComponent();
	MeshComponent* tMesh = new MeshComponent();
	LabelComponent* tLabel = new LabelComponent();
	PhysicComponent* tPhysic = new PhysicComponent();
	VelocityComponent* tVelocity = new VelocityComponent();
	CollisionComponent* tColl = new CollisionComponent();
	SoundCollisionComponent* tSoundColl = new SoundCollisionComponent();

	////////set component values
	////////we ignore this and use the initialization values for test
	///////WARNINIG: We should call the graphic engine for loading a texture then
	////////////return the ID To meshComponent
	//tLabel->mLabel = Label::Pad;
	//tColl->Dim = vec2(0.5, 0.5);
	//EntityFactory::EntityBlueprint tPadBlueprint;
	//tPadBlueprint[TransformType] = tTrans;
	//tMesh->mMaterialID = tGraphicsInterFace->CreateTexture(L"Textures/PadTex.dds");
	//tPadBlueprint[MeshType] = tMesh;
	//tPadBlueprint[LabelType] = tLabel;
	//tPadBlueprint[CollisionType] = tColl;
	//tPadBlueprint[TransformType] = tTrans;
	//tPadBlueprint[VelocityType] = tVelocity;
	//
	//mEntityFactory->RegisterEntityTemplate("Padda", tPadBlueprint);

	///ska skapa en BluePrint


	////Med Textfil

	EntityFactory::EntityBlueprint tPadBlueprint;///////tPadBluePrint
	//tTrans = new TransformComponent();
	//tMesh = new MeshComponent();
	//tLabel = new LabelComponent();
	//tPhysic = new PhysicComponent();
	//tVelocity = new VelocityComponent();
	//tColl = new CollisionComponent();
	string tBlueprintNamn = "";
	vector<string> mEntitiyVector;
	mEntitiyVector = TextFileReader::ReadTextFile("Entities/Pad.txt");
	//string TestSomSatan = "";
	for (size_t i = 0; i < mEntitiyVector.size(); i++)
	{
		//TestSomSatan = mEntitiyVector[i];
		if (mEntitiyVector[i].compare("xEntity") == 0)
		{
			++i;
			tBlueprintNamn = mEntitiyVector[i];
		}
		else if (mEntitiyVector[i].compare("xLabel") == 0)
		{
			i++;
			tLabel->mLabel = Label::Pad;
			tPadBlueprint[LabelType] = tLabel;
			///////////Kolla vilken label det är i LabelComponent
		}

		else if (mEntitiyVector[i].compare("xTransform") == 0)
		{
			tPadBlueprint[TransformType] = tTrans;
		}
		else if (mEntitiyVector[i].compare("xVelocity") == 0)
		{
			tPadBlueprint[VelocityType] = tVelocity;
		}
		else if (mEntitiyVector[i].compare("xCollision") == 0)
		{
			//i++;
			//int tXColl=;
			//int tYColl=;

			tColl->Dim = vec2(1, 0.5);
			tPadBlueprint[CollisionType] = tColl;
		}
		else if (mEntitiyVector[i].compare("xMesh") == 0)
		{
			++i;
			//std::wstring name(L+mEntit iyVector[i]);
			//const wchar_t* szName = name.c_str();
			std::wstring widestr = std::wstring(mEntitiyVector[i].begin(), mEntitiyVector[i].end());
			const wchar_t* widecstr = widestr.c_str();
			tMesh->mMaterialID = tGraphicsInterFace->CreateTexture(mEntitiyVector[i]);///Här ska vi byta textur!!
			




			////////Sen fixa meshen till objektet när objLoader e klar så borde denna fungera
			++i;
			const char * tConstChar = mEntitiyVector[i].c_str();  ///HÄR NÄR KONY FIXAT BOXANDET!
			tMesh->mMeshID = tGraphicsInterFace->CreateObject(mEntitiyVector[i]);
			tPadBlueprint[MeshType] = tMesh;
		}


	}

	SoundEngine::GetInstance()->LoadSoundToMemory("PadCollision.mp3", tSoundColl->SoundID);
	tPadBlueprint[SoundCollisionType] = tSoundColl;
	mEntityFactory->RegisterEntityTemplate("Padda", tPadBlueprint);

	/////ska skapa en BluePrint











	/////////////////////////////////BLOCK///////////////////
	EntityFactory::EntityBlueprint tBlockBlueprint;

	//Component values might be silly and have to be altered later
	tTrans = new TransformComponent();
	tMesh = new MeshComponent();
	tColl = new CollisionComponent();
	tLabel = new LabelComponent();
	tSoundColl = new SoundCollisionComponent();
	ScoreValueComponent* tScoreValue = new ScoreValueComponent();

	SoundEngine::GetInstance()->LoadSoundToMemory("BlockCollision.wav", tSoundColl->SoundID);
	tLabel->mLabel = Label::Box;
	tColl->Dim = vec2(0.5, 0.5);
	tColl->mType = AABB;
	tMesh->mMaterialID = tGraphicsInterFace->CreateTexture("test2in1pic");///Här ska vi byta textur!!
	tMesh->mMeshID = tGraphicsInterFace->CreateObject("Object/Block.obj");

	tBlockBlueprint[TransformType] = tTrans;
	tBlockBlueprint[MeshType] = tMesh;
	tBlockBlueprint[VelocityType] = tVelocity;
	tBlockBlueprint[CollisionType] = tColl;
	tBlockBlueprint[LabelType] = tLabel;
	tBlockBlueprint[SoundCollisionType] = tSoundColl;
	tBlockBlueprint[ScoreValueType] = tScoreValue;

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
	tMesh->mMaterialID = tGraphicsInterFace->CreateTexture("davai");//prov
	tMesh->mMeshID = tGraphicsInterFace->CreateObject("Object/Boll.obj");
	tBallBlueprint[TransformType] = tTrans;
	tBallBlueprint[MeshType] = tMesh;
	tBallBlueprint[LabelType] = tLabel;
	tBallBlueprint[CollisionType] = tColl;

	

	mEntityFactory->RegisterEntityTemplate("Ball", tBallBlueprint);


	///////////////////////////////////GOALBLOCK///////////////////
	EntityFactory::EntityBlueprint tGoalBlockBlueprint;

	//Component values might be silly and have to be altered later
	tTrans = new TransformComponent();
	tMesh = new MeshComponent();
	tVelocity = new VelocityComponent();
	tLabel = new LabelComponent();
	tColl = new CollisionComponent();
	tSoundColl = new SoundCollisionComponent();


	SoundEngine::GetInstance()->LoadSoundToMemory("GoalBlockCollision.mp3", tSoundColl->SoundID);
	tColl->mType = CollisionGeo::AABB;
	tColl->Dim = vec2(0.5, 0.5);
	tLabel->mLabel = Label::GoalBlock;
	tMesh->mMaterialID = tGraphicsInterFace->CreateTexture("Textures/GoalTexture");///Här ska vi byta textur!!
	tMesh->mMeshID = tGraphicsInterFace->CreateObject("Object/Block.obj");
	tGoalBlockBlueprint[TransformType] = tTrans;
	tGoalBlockBlueprint[MeshType] = tMesh;
	tGoalBlockBlueprint[VelocityType] = tVelocity;
	tGoalBlockBlueprint[LabelType] = tLabel;
	tGoalBlockBlueprint[CollisionType] = tColl;
	tGoalBlockBlueprint[SoundCollisionType] = tSoundColl;
	mEntityFactory->RegisterEntityTemplate("GoalBlock", tGoalBlockBlueprint);
	////////////////////SIDE WALL///////////////////////////
	EntityFactory::EntityBlueprint tWallBlueprint;

	tTrans = new TransformComponent();
	tColl = new CollisionComponent();
	tSoundColl = new SoundCollisionComponent();

	SoundEngine::GetInstance()->LoadSoundToMemory("WallCollision.wav", tSoundColl->SoundID);
	tColl->mType = CollisionGeo::AABB;
	tColl->Dim = vec2(30,0.2f);
	
	tWallBlueprint[TransformType] = tTrans;
	tWallBlueprint[CollisionType] = tColl;
	tWallBlueprint[SoundCollisionType] = tSoundColl;
	//tWallBlueprint[MeshType] = tMesh;
	mEntityFactory->RegisterEntityTemplate("HorWall", tWallBlueprint);

	///////////////////TOP-BOT WALL////////////////
	EntityFactory::EntityBlueprint tWall2Blueprint;

	tTrans = new TransformComponent();
	tColl = new CollisionComponent();
	tSoundColl = new SoundCollisionComponent();


	SoundEngine::GetInstance()->LoadSoundToMemory("WallCollision.wav", tSoundColl->SoundID);
	tColl->mType = CollisionGeo::AABB;
	tColl->Dim = vec2(0.2f, 30.0f);

	tWall2Blueprint[TransformType] = tTrans;
	tWall2Blueprint[CollisionType] = tColl;
	tWall2Blueprint[SoundCollisionType] = tSoundColl;
	//tWall2Blueprint[MeshType] = tMesh;
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
	EntityID tPaddID = tNewID;
	TransformComponent* tTrans = GetComponent<TransformComponent>(tNewID);
	tTrans->mPosition = vec3(0, -8, 8);
	int derp = GetComponent<LabelComponent>(tNewID)->mLabel;
	GetComponent<VelocityComponent>(tNewID)->mSpeed = 10.0f;
	
	//Reading The level from textfile
	vector<string> mLevelTextVector;
	mLevelTextVector = TextFileReader::ReadTextFile(pWorldName);
	int t_forLoopI = mLevelTextVector.size();
	int t_forLooPJ = 0;
	if (t_forLoopI != 0)
	{
		t_forLooPJ = mLevelTextVector[2].size();
	}
	
	for (size_t i = 0; i < t_forLoopI; i++)
	{
		for (size_t j = 0; j < t_forLooPJ; j++)
		{
			if (mLevelTextVector[i].at(j) == 'X')
			{
				tNewID = mEntityFactory->CreateEntity("Block");
				tTrans = GetComponent<TransformComponent>(tNewID);
				tTrans->mPosition.x = j - (float)t_forLooPJ/2;
				tTrans->mPosition.y = t_forLoopI - i;

				//set value of the blocks. Should be read from file
				GetComponent<ScoreValueComponent>(tNewID)->value = 50;
			}
			else if (mLevelTextVector[i].at(j) == 'G')
			{
				tNewID = mEntityFactory->CreateEntity("GoalBlock");
				tTrans = GetComponent<TransformComponent>(tNewID);
				tTrans->mPosition.x = j - (float)t_forLooPJ / 2;
				tTrans->mPosition.y = t_forLoopI - i;

			}
		}
	}


	// This is where the score for the map is set. Should be read properly when loading map..
	unordered_map<string, void*> payload;
	int* score = new int();
	*score = 1000;
	payload["score"] = (void*)score;
	EventManager::GetInstance()->BroadcastEvent("SetScore", payload);



	
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


	tNewID = mEntityFactory->CreateEntity("Ball");
	ComponentTable::GetInstance()->AddComponent(tNewID, AttachedType);
	AttachedComponent* tAtt = GetComponent<AttachedComponent>(tNewID);
	tAtt->attachedTo = tPaddID;
	tAtt->relPos = vec3(0, 1, 0);

	//tTrans = GetComponent<TransformComponent>(tNewID);
	//tTrans->mPosition.x = -2;
	//tTrans->mPosition.y = -1;

	//VelocityComponent* tVel = GetComponent<VelocityComponent>(tNewID);
	//tVel->mSpeed = 8.0f;
	//vec3 tStartDirection = vec3(1.0f, 2.0f, 0.0f).Normalize();
	//tVel->mDirection.x = tStartDirection.x;
	//tVel->mDirection.y = tStartDirection.y;
	//tVel->mDirection.z = tStartDirection.z;


	////////////////////GOAL//////////////////////////
	//tNewID = mEntityFactory->CreateEntity("GoalBlock");
	//GetComponent<TransformComponent>(tNewID)->mPosition = vec3(0, 0, 0);
	//ComponentTable::GetInstance()->AddComponent(tNewID, LabelType);
	//GetComponent<LabelComponent>(tNewID)->mLabel = Label::GoalBlock;


	//////////////////TOP BOT WALL///////////////////
	tNewID = mEntityFactory->CreateEntity("HorWall");
	GetComponent<TransformComponent>(tNewID)->mPosition = vec3(0,t_forLoopI+1,8);

	tNewID = mEntityFactory->CreateEntity("HorWall");
	GetComponent<TransformComponent>(tNewID)->mPosition = vec3(0, -10, 8);
	ComponentTable::GetInstance()->AddComponent(tNewID, LabelType);
	LabelComponent* tLabel = GetComponent<LabelComponent>(tNewID);
	tLabel->mLabel = Label::BottomArea;

	/////////////////SIDE WALLS/////////////////////////
	tNewID = mEntityFactory->CreateEntity("VerWall");
	GetComponent<TransformComponent>(tNewID)->mPosition = vec3(t_forLooPJ / 2 + 1, 0, 8);

	tNewID = mEntityFactory->CreateEntity("VerWall");
	GetComponent<TransformComponent>(tNewID)->mPosition = vec3(-t_forLooPJ / 2 - 1, 0, 8);

}

void LevelManager::DegenerateWorld()
{
	EntityManager* pEntManager = pEntManager->GetInstance();
	int tMaxEnt = pEntManager->GetLastEntity();

	for (int i = 0; i < tMaxEnt; i++)
	{
		pEntManager->RemoveEntity(i);
	}
}
