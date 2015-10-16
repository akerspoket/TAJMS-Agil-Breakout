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
#include "GraphicsInterface.h"
#include <iostream>
#include "ScoreValueComponent.h"
#include "PowerUpComponent.h"
#include "PowerUpContainComponent.h"
#include <random>

#include "MenyButtonComponent.h"
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
	MenyButtonComponent* tMenButComp = new MenyButtonComponent();
	AttachedComponent* tAttachComp = new AttachedComponent();


	//////////////////////Creates pad entity blueprint fron text file
	EntityFactory::EntityBlueprint tPadBlueprint;///////tPadBluePrint
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
			tLabel->AddLabel(Pad);
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

			tColl->Dim = vec2(2.5, 1);
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


	/////////////////////////////////BLOCK///////////////////
	EntityFactory::EntityBlueprint tBlockBlueprint;

	//Component values might be silly and have to be altered later
	tTrans = new TransformComponent();
	tMesh = new MeshComponent();
	tColl = new CollisionComponent();
	tLabel = new LabelComponent();
	tSoundColl = new SoundCollisionComponent();
	ScoreValueComponent* tScoreValue = new ScoreValueComponent();//lägga högst upp????????????????

	SoundEngine::GetInstance()->LoadSoundToMemory("BlockCollision.wav", tSoundColl->SoundID);
	tLabel->AddLabel(Box);
	tColl->Dim = vec2(0.5, 0.5);
	tColl->mType = AABB;
	tMesh->mMaterialID = tGraphicsInterFace->CreateTexture("Textures/BoxTexture2");///Här ska vi byta textur!!
	tMesh->mMeshID = tGraphicsInterFace->CreateObject("Object/Chest.obj");

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
	tLabel->AddLabel(Ball);

	tColl->mType = CollisionGeo::Sphere;
	tColl->Dim.x = 0.2f;
	tMesh->mMaterialID = tGraphicsInterFace->CreateTexture("Textures/CanonBall");//prov
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
	tColl->Dim = vec2(2.5, 0.5);
	tLabel->AddLabel(GoalBlock);
	tMesh->mMaterialID = tGraphicsInterFace->CreateTexture("Textures/ShipTextureGoal");///Här ska vi byta textur!!
	tMesh->mMeshID = tGraphicsInterFace->CreateObject("Object/Ship.obj");
	tGoalBlockBlueprint[TransformType] = tTrans;
	tGoalBlockBlueprint[MeshType] = tMesh;
	tGoalBlockBlueprint[VelocityType] = tVelocity;
	tGoalBlockBlueprint[LabelType] = tLabel;
	tGoalBlockBlueprint[CollisionType] = tColl;
	tGoalBlockBlueprint[SoundCollisionType] = tSoundColl;
	mEntityFactory->RegisterEntityTemplate("GoalBlock", tGoalBlockBlueprint);
	////////////////////TOP-BOT WALL///////////////////////////
	EntityFactory::EntityBlueprint tWallBlueprint;

	tTrans = new TransformComponent();
	tColl = new CollisionComponent();
	tSoundColl = new SoundCollisionComponent();
	tLabel = new LabelComponent();
	SoundEngine::GetInstance()->LoadSoundToMemory("WallCollision.wav", tSoundColl->SoundID);
	tColl->mType = CollisionGeo::AABB;
	tColl->Dim = vec2(30, 0.2f);
	tLabel->AddLabel(Wall);

	tWallBlueprint[TransformType] = tTrans;
	tWallBlueprint[CollisionType] = tColl;
	tWallBlueprint[SoundCollisionType] = tSoundColl;
	//tWallBlueprint[MeshType] = tMesh;
	tWallBlueprint[LabelType] = tLabel;
	mEntityFactory->RegisterEntityTemplate("HorWall", tWallBlueprint);

	///////////////////SIDE WALL////////////////
	EntityFactory::EntityBlueprint tWall2Blueprint;

	tTrans = new TransformComponent();
	tColl = new CollisionComponent();
	tSoundColl = new SoundCollisionComponent();
	tMesh = new MeshComponent();
	tLabel = new LabelComponent();
	SoundEngine::GetInstance()->LoadSoundToMemory("WallCollision.wav", tSoundColl->SoundID);
	tColl->mType = CollisionGeo::AABB;
	tColl->Dim = vec2(1.5f, 30.0f);
	tLabel->AddLabel(Wall);
	tMesh->mMeshID = tGraphicsInterFace->CreateObject("Object/SideWall.obj");
	tWall2Blueprint[TransformType] = tTrans;
	tWall2Blueprint[CollisionType] = tColl;
	tWall2Blueprint[SoundCollisionType] = tSoundColl;
	tWall2Blueprint[MeshType] = tMesh;
	tWall2Blueprint[LabelType] = tLabel;
	mEntityFactory->RegisterEntityTemplate("VerWall", tWall2Blueprint);

	//////////////////////MenuButtonBlock///////////////
	EntityFactory::EntityBlueprint tMenuButtonBlock;

	tTrans = new TransformComponent();
	tMesh = new MeshComponent();

	
	tMenuButtonBlock[MenyButtonType] = tMenButComp;
	tMenuButtonBlock[TransformType] = tTrans;
	tMesh->mMaterialID = tGraphicsInterFace->CreateTexture("Textures/Background");//Will be changed later for each specific button
	tMesh->mMeshID = tGraphicsInterFace->CreateObject("Object/Button.obj");
	tMenuButtonBlock[MeshType] = tMesh;
	mEntityFactory->RegisterEntityTemplate("MenuButtonBlock", tMenuButtonBlock);

	/////MenuPointer
	EntityFactory::EntityBlueprint tMenuPtrBlueprint;

	tTrans = new TransformComponent();
	tAttachComp = new AttachedComponent();
	tMesh = new MeshComponent();
	tLabel = new LabelComponent();


	tMenuPtrBlueprint[TransformType] = tTrans;
	tMesh->mMaterialID = tGraphicsInterFace->CreateTexture("Textures/CanonBall");
	tMesh->mMeshID = tGraphicsInterFace->CreateObject("Object/Boll.obj");
	tAttachComp->relPos = vec3(-3, 0, 0);
	tMenuPtrBlueprint[AttachedType] = tAttachComp;
	tMenuPtrBlueprint[MeshType] = tMesh;
	tLabel->AddLabel(MenuPointer);
	tMenuPtrBlueprint[LabelType] = tLabel;
	
	mEntityFactory->RegisterEntityTemplate("MenuPointer", tMenuPtrBlueprint);


	//////Background
	EntityFactory::EntityBlueprint tBackgroundBlueprint;
	tMesh = new MeshComponent();
	tTrans = new TransformComponent();
	tMesh->mMeshID = tGraphicsInterFace->CreateObject("Object/Background.obj");
	tMesh->mMaterialID = tGraphicsInterFace->CreateTexture("Textures/Background");
	tTrans->mPosition = vec3(0, 0, 10);
	tBackgroundBlueprint[MeshType] = tMesh;
	tBackgroundBlueprint[TransformType] = tTrans;
	mEntityFactory->RegisterEntityTemplate("BackgroundBlock", tBackgroundBlueprint);


	///////////DEBUG POWERUP/////////
	EntityFactory::EntityBlueprint tPowerUpBlueprint;
	tMesh = new MeshComponent();
	tTrans = new TransformComponent();
	tVelocity = new VelocityComponent();
	tColl = new CollisionComponent();
	PowerUpContainComponenet* tPupContain = new PowerUpContainComponenet();
	tMesh->mMeshID = tGraphicsInterFace->CreateObject("Object/Boll.obj");
	tMesh->mMaterialID = tGraphicsInterFace->CreateTexture("Textures/ShipTextureGoal");
	tTrans->mPosition = vec3(0, 0, 8);
	tVelocity->mDirection = vec3(0, -1, 0);
	tVelocity->mSpeed = 5;
	tPupContain->duration = 2;
	tPupContain->type = SpeedUp;
	tColl->Dim = vec2(0.5, 0.5);
	tColl->mType = Sphere;
	tPowerUpBlueprint[MeshType] = tMesh;
	tPowerUpBlueprint[TransformType] = tTrans;
	tPowerUpBlueprint[VelocityType] = tVelocity;
	tPowerUpBlueprint[PowerUpContainType] = tPupContain;
	tPowerUpBlueprint[CollisionType] = tColl;
	mEntityFactory->RegisterEntityTemplate("DEBUGPUP", tPowerUpBlueprint);



}
void LevelManager::GenerateMainMenu()
{
	EntityID tNewID = mEntityFactory->CreateEntity("MenuButtonBlock");
	TransformComponent* tTrans = GetComponent<TransformComponent>(tNewID);
	MenyButtonComponent* tMenButComp = GetComponent<MenyButtonComponent>(tNewID);
	GetComponent<MeshComponent>(tNewID)->mMaterialID = GraphicsInterface::GetSingleton()->CreateTexture("Textures/StartButtonTexture");
	tMenButComp->mButtonBelong = MainMenu;
	tMenButComp->mButtonName = MainStart;
	tTrans->mPosition = vec3(0, 8, 8);



	EntityID tPointerID = mEntityFactory->CreateEntity("MenuPointer");
	AttachedComponent* tAttComp = GetComponent<AttachedComponent>(tPointerID);
	tAttComp->attachedTo = tNewID;

	tNewID = mEntityFactory->CreateEntity("MenuButtonBlock");
	GetComponent<MeshComponent>(tNewID)->mMaterialID = GraphicsInterface::GetSingleton()->CreateTexture("Textures/OptionsButtonTexture");
	tMenButComp = GetComponent<MenyButtonComponent>(tNewID);
	tMenButComp->mButtonBelong = MainMenu;
	tMenButComp->mButtonName = MainOption;
	tTrans = GetComponent<TransformComponent>(tNewID);
	tTrans->mPosition = vec3(0, 4, 8);

	tNewID = mEntityFactory->CreateEntity("MenuButtonBlock");
	GetComponent<MeshComponent>(tNewID)->mMaterialID = GraphicsInterface::GetSingleton()->CreateTexture("Textures/HighscoreButtonTexture");
	tMenButComp = GetComponent<MenyButtonComponent>(tNewID);
	tMenButComp->mButtonBelong = MainMenu;
	tMenButComp->mButtonName = MainHighscore;
	tTrans = GetComponent<TransformComponent>(tNewID);
	tTrans->mPosition = vec3(0, 0, 8);

	tNewID = mEntityFactory->CreateEntity("MenuButtonBlock");
	GetComponent<MeshComponent>(tNewID)->mMaterialID = GraphicsInterface::GetSingleton()->CreateTexture("Textures/TutorialButtonTexture");
	tMenButComp = GetComponent<MenyButtonComponent>(tNewID);
	tMenButComp->mButtonBelong = MainMenu;
	tMenButComp->mButtonName = MainTutorial;
	tTrans = GetComponent<TransformComponent>(tNewID);
	tTrans->mPosition = vec3(0, -4, 8);

	tNewID = mEntityFactory->CreateEntity("MenuButtonBlock");
	GetComponent<MeshComponent>(tNewID)->mMaterialID = GraphicsInterface::GetSingleton()->CreateTexture("Textures/ExitButtonTexture");
	tMenButComp = GetComponent<MenyButtonComponent>(tNewID);
	tMenButComp->mButtonBelong = MainMenu;
	tMenButComp->mButtonName = MainQuit;
	tTrans = GetComponent<TransformComponent>(tNewID);
	tTrans->mPosition = vec3(0, -8, 8);

}


void LevelManager::GenerateDeathScreen()
{
	EntityID tNewID = mEntityFactory->CreateEntity("MenuButtonBlock");
	GetComponent<MeshComponent>(tNewID)->mMaterialID = GraphicsInterface::GetSingleton()->CreateTexture("Textures/RestartLevelButtonTexture");
	TransformComponent* tTrans = GetComponent<TransformComponent>(tNewID);
	MenyButtonComponent* tMenButComp = GetComponent<MenyButtonComponent>(tNewID);
	tMenButComp->mButtonBelong = DeathMenu;
	tMenButComp->mButtonName = DeathRestartLevel;
	tTrans->mPosition = vec3(0, 2, 8);

	EntityID tPointerID = mEntityFactory->CreateEntity("MenuPointer");
	AttachedComponent* tAttComp = GetComponent<AttachedComponent>(tPointerID);
	tAttComp->attachedTo = tNewID;


	tNewID = mEntityFactory->CreateEntity("MenuButtonBlock");
	GetComponent<MeshComponent>(tNewID)->mMaterialID = GraphicsInterface::GetSingleton()->CreateTexture("Textures/MainMenuButtonTexture");
	tMenButComp = GetComponent<MenyButtonComponent>(tNewID);
	tMenButComp->mButtonBelong = DeathMenu;
	tMenButComp->mButtonName = DeathQuitToMainMenu;
	tTrans = GetComponent<TransformComponent>(tNewID);
	tTrans->mPosition = vec3(0, -2, 8);

}

void LevelManager::GeneratePauseScreen()
{
	EntityID tNewID = mEntityFactory->CreateEntity("MenuButtonBlock");
	GetComponent<MeshComponent>(tNewID)->mMaterialID = GraphicsInterface::GetSingleton()->CreateTexture("Textures/ResumeButtonTexture");
	TransformComponent* tTrans = GetComponent<TransformComponent>(tNewID);
	MenyButtonComponent* tMenButComp = GetComponent<MenyButtonComponent>(tNewID);
	tMenButComp->mButtonBelong = PauseMenu;
	tMenButComp->mButtonName = PauseResume;
	tTrans->mPosition = vec3(0, 4, 8);


	EntityID tPointerID = mEntityFactory->CreateEntity("MenuPointer");
	AttachedComponent* tAttComp = GetComponent<AttachedComponent>(tPointerID);
	tAttComp->attachedTo = tNewID;



	tNewID = mEntityFactory->CreateEntity("MenuButtonBlock");
	GetComponent<MeshComponent>(tNewID)->mMaterialID = GraphicsInterface::GetSingleton()->CreateTexture("Textures/RestartLevelButtonTexture");
	tMenButComp = GetComponent<MenyButtonComponent>(tNewID);
	tMenButComp->mButtonBelong = PauseMenu;
	tMenButComp->mButtonName = PauseRestartLevel;
	tTrans = GetComponent<TransformComponent>(tNewID);
	tTrans->mPosition = vec3(0, 0, 8);

	tNewID = mEntityFactory->CreateEntity("MenuButtonBlock");
	GetComponent<MeshComponent>(tNewID)->mMaterialID = GraphicsInterface::GetSingleton()->CreateTexture("Textures/MainMenuButtonTexture");
	tMenButComp = GetComponent<MenyButtonComponent>(tNewID);
	tMenButComp->mButtonBelong = PauseMenu;
	tMenButComp->mButtonName = PauseQuitToMainMenu;
	tTrans = GetComponent<TransformComponent>(tNewID);
	tTrans->mPosition = vec3(0, -4, 8);
}


void PoopLabels() //Silly method...put it in my bum now my bumholes numb and eats plums
{
	EntityManager* tEntManager = tEntManager->GetInstance();
	ComponentTable* tCompTable = tCompTable->GetInstance();
	int tMaxEnt = tEntManager->GetLastEntity();

	for (int i = 0; i > tMaxEnt; i++)
	{
		GetComponent<LabelComponent>(i)->mLabel = None;
	}
}
void LevelManager::GenerateWorld(string pWorldName)
{

	PoopLabels();

	////////////////////DEBUG POWERUP//////////
	EntityID tPupID = mEntityFactory->CreateEntity("DEBUGPUP");
	GetComponent<PowerUpContainComponenet>(tPupID)->duration = 3;
	GetComponent<PowerUpContainComponenet>(tPupID)->type = InvertDown;



	////////////////////PADDA//////////////////
	EntityID tNewID = mEntityFactory->CreateEntity("Padda");
	EntityID tPaddID = tNewID;
	TransformComponent* tTrans = GetComponent<TransformComponent>(tNewID);
	tTrans->mPosition = vec3(0, -8, 8);
	int derp = GetComponent<LabelComponent>(tNewID)->mLabel;
	GetComponent<VelocityComponent>(tNewID)->mSpeed = 10.0f;
	
	/////TEST ADDING SPEEDUP POWERUP////////
	//ComponentTable::GetInstance()->AddComponent(tNewID, PowerUpType);
	//unordered_map<string, void*> pupPayload;
	//EntityID* entID = new EntityID();
	//*entID = tNewID;
	//pupPayload["EntityID"] = entID;
	//short* mask = new short();
	//*mask = SpeedUp;
	//pupPayload["mask"] = mask;
	//float* duration = new float;
	//*duration = 2;
	//pupPayload["duration"] = duration;
	//EventManager::GetInstance()->BroadcastEvent("PowerUpPickedUp", pupPayload);
	//////END TEST/////////////////

	//EventManager::GetInstance()->BroadcastEvent("PowerUpPickedUp", pupPayload);
	////END TEST/////////////////

	//////////////////BLOCKS/////////////////////
	//Reading The level from textfile
	vector<string> mLevelTextVector;
	mLevelTextVector = TextFileReader::ReadTextFile(pWorldName);
	int t_forLoopI = mLevelTextVector.size();
	int t_forLooPJ = 0;
	if (t_forLoopI != 0)
	{
		t_forLooPJ = mLevelTextVector[2].size();
	}
	
	int* tScore = new int();


	vector<short> possiblePups;
	possiblePups.push_back(SpeedUp);
	//possiblePups.push_back(BallNet);
	//possiblePups.push_back(Piercing);
	//possiblePups.push_back(MagnetPUp);


	vector<float> pupDurations;
	pupDurations.push_back(2); 
	pupDurations.push_back(2);
	pupDurations.push_back(2);
	pupDurations.push_back(2);

	//Pup generation stuff
	std::default_random_engine generator;
	float chanceOfPup = 100;
	int max = 100 / chanceOfPup;

	for (size_t i = 0; i < t_forLoopI; i++)
	{
		for (size_t j = 0; j < t_forLooPJ; j++)
		{
			if (mLevelTextVector[i].at(j) == 'X')
			{
				tNewID = mEntityFactory->CreateEntity("Block");
				tTrans = GetComponent<TransformComponent>(tNewID);
				tTrans->mPosition.x = j - (float)t_forLooPJ / 2;
				tTrans->mPosition.y = t_forLoopI - i;
				tTrans->mPosition.z = 8;

				//See if block gets a power up
				std::uniform_int_distribution<int> distribution(1, max);
				int hit = distribution(generator);

				if (hit == 1)
				{
					//block got pup. Determine which pup
					std::uniform_int_distribution<int> distribution2(0, possiblePups.size()-1);
					int pupIndex = rand() % (possiblePups.size());
					ComponentTable::GetInstance()->AddComponent(tNewID, PowerUpContainType);
					GetComponent<PowerUpContainComponenet>(tNewID)->type = possiblePups[pupIndex];
					GetComponent<PowerUpContainComponenet>(tNewID)->duration = pupDurations[pupIndex];
				}

				//set value of the blocks. Should be read from file
				GetComponent<ScoreValueComponent>(tNewID)->value = 50;
				//Max score is the sum of the score of each block
				*tScore += 50;
			}
			else if (mLevelTextVector[i].at(j) == 'G')
			{
				tNewID = mEntityFactory->CreateEntity("GoalBlock");
				tTrans = GetComponent<TransformComponent>(tNewID);
				tTrans->mPosition.x = j - (float)t_forLooPJ / 2;
				tTrans->mPosition.y = t_forLoopI - i;
				tTrans->mPosition.z = 8;

			}
		}
	}


	// This is where the score for the map is set. Should be read properly when loading map..
	unordered_map<string, void*> payload;
	payload["score"] = (void*)tScore;
	EventManager::GetInstance()->BroadcastEvent("SetScore", payload);


	//////////////////////////BALL////////////////////
	tNewID = mEntityFactory->CreateEntity("Ball");
	ComponentTable::GetInstance()->AddComponent(tNewID, AttachedType);
	AttachedComponent* tAtt = GetComponent<AttachedComponent>(tNewID);
	tAtt->attachedTo = tPaddID;
	tAtt->relPos = vec3(0, 1.3, 0);


	//////////////////TOP BOT WALL///////////////////
	tNewID = mEntityFactory->CreateEntity("HorWall");
	GetComponent<TransformComponent>(tNewID)->mPosition = vec3(0, t_forLoopI + 1, 8);

	tNewID = mEntityFactory->CreateEntity("HorWall");
	GetComponent<TransformComponent>(tNewID)->mPosition = vec3(0, -10, 8);
	ComponentTable::GetInstance()->AddComponent(tNewID, LabelType);
	LabelComponent* tLabel = GetComponent<LabelComponent>(tNewID);
	tLabel->AddLabel(BottomArea);

	/////////////////SIDE WALLS/////////////////////////
	tNewID = mEntityFactory->CreateEntity("VerWall");
	GetComponent<TransformComponent>(tNewID)->mPosition = vec3(t_forLooPJ / 2 + 3, 0, 8);
	GetComponent<MeshComponent>(tNewID)->mMaterialID = GraphicsInterface::GetSingleton()->CreateTexture("Textures/LeftSideBeach");

	tNewID = mEntityFactory->CreateEntity("VerWall");
	GetComponent<TransformComponent>(tNewID)->mPosition = vec3(-t_forLooPJ / 2 - 3, 0, 8);
	GetComponent<MeshComponent>(tNewID)->mMaterialID = GraphicsInterface::GetSingleton()->CreateTexture("Textures/RightSideBeach");

	/////////////////BACKGROUND/////////////////////////
	tNewID = mEntityFactory->CreateEntity("BackgroundBlock");
	

}

void LevelManager::DegenerateMenu()
{
	EntityManager* tEntManager = tEntManager->GetInstance();
	ComponentTable* tCompTable = tCompTable->GetInstance();
	int tMaxEnt = tEntManager->GetLastEntity();

	for (int i = 0; i < tMaxEnt; i++)
	{
		if (tCompTable->HasComponent(i, MenyButtonType))
		{
			tEntManager->RemoveEntity(i);
		}
		else if (tCompTable->HasComponent(i, LabelType))
		{
			if (GetComponent<LabelComponent>(i)->HasLabel(MenuPointer))
			{
				tEntManager->RemoveEntity(i);
			}
		}
	}
}

void LevelManager::DegenerateEverything()
{
	EntityManager* pEntManager = pEntManager->GetInstance();
	int tMaxEnt = pEntManager->GetLastEntity();

	for (int i = 0; i < tMaxEnt; i++)
	{
		pEntManager->RemoveEntity(i);
	}
}
