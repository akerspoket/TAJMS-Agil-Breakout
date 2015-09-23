#include "LevelManager.h"
#include "StorageShelf.h"
#include "TransformComponent.h"
#include "MeshComponent.h"
#include "LabelComponent.h"
#include "PhysicComponent.h"
#include "VelocityComponent.h"
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
	EntityFactory::EntityBlueprint tBlueprint;

	TransformComponent* tTrans = new TransformComponent();
	MeshComponent* tMesh = new MeshComponent();
	LabelComponent* tLabel = new LabelComponent();
	PhysicComponent* tPhysic = new PhysicComponent();
	VelocityComponent* tVelocity = new VelocityComponent();



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
	
	//////////////////////////////////////////add padda to blueprint
	
	//tBlueprint[TransformType] = tTrans;
	tBlueprint[MeshType] = tMesh;
	tBlueprint[LabelType] = tLabel;

	mEntityFactory->RegisterEntityTemplate("Padda", tBlueprint);

	///////////////////////////////////add block to blueprint
	EntityFactory::EntityBlueprint tBlockBlueprint;

	//Component values might be silly and have to be altered later
	tTrans = new TransformComponent();
	tMesh = new MeshComponent();
	tVelocity = new VelocityComponent();
	//tMesh->mMaterialID = tGraphicsInterFace->CreateTexture(L"test2in1pic.dds");///Här ska vi byta textur!!
	tBlockBlueprint[TransformType] = tTrans;
	tBlockBlueprint[MeshType] = tMesh;
	tBlockBlueprint[VelocityType] = tVelocity;

	mEntityFactory->RegisterEntityTemplate("Block", tBlockBlueprint);

	//////////////////////////////////add ball to blueprint
	EntityFactory::EntityBlueprint tBallBlueprint;

	//Component values might be silly and have to be altered later
	tTrans = new TransformComponent();
	tMesh = new MeshComponent();
	tLabel = new LabelComponent();

	//We set the label here since it never changes
	tLabel->mLabel = Label::Ball;

	tBallBlueprint[TransformType] = tTrans;
	tBallBlueprint[MeshType] = tMesh;
	tBallBlueprint[LabelType] = tLabel;

	mEntityFactory->RegisterEntityTemplate("Ball", tBallBlueprint);

}

void LevelManager::GenerateWorld(string pWorldName)
{

	//GraphicsInterface* tGraphicsInterFace = GraphicsInterface::GetSingleton();
	//tGraphicsInterFace->CreateTexture(L"test2in1pic.dds");
	//tGraphicsInterFace->CreateObject("Box.obj");


	/////Creating a Pad for the game
	EntityID tNewID = mEntityFactory->CreateEntity("Padda");
	TransformComponent* tTrans = GetComponent<TransformComponent>(tNewID);
	tTrans->mPosition.x = 1.0f;
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




	//Create blocks
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

	//Create the ball
	float tStartPositionX = 0;
	float tStartPositionY = 0;

	tNewID = mEntityFactory->CreateEntity("Ball");
	tTrans = GetComponent<TransformComponent>(tNewID);
	tTrans->mPosition.x = tStartPositionX;
	tTrans->mPosition.y = tStartPositionY;

	VelocityComponent* tVel = GetComponent<VelocityComponent>(tNewID);
	tVel->mSpeed = 0.001f;
	vec3 tStartDirection = vec3(1.0f, 1.0f, 0.0f);
	tVel->mDirection.x = tStartDirection.x;
	tVel->mDirection.y = tStartDirection.y;
	tVel->mDirection.z = tStartDirection.z;

	//Create the goal block
	tNewID = mEntityFactory->CreateEntity("Block");
	ComponentTable::GetInstance()->AddComponent(tNewID, LabelType);
	GetComponent<LabelComponent>(tNewID)->mLabel = Label::Goal;


}