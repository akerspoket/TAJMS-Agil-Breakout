#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Breakout - Agil/SoundEngine.h"
#include "../Breakout - Agil/SoundEngine.cpp"
#include "../Breakout - Agil/Constants.h"
#include "../Breakout - Agil/EntityManager.h"
#include "../Breakout - Agil/EntityManager.cpp"
#include "../Breakout - Agil/EntityFactory.h"
#include "../Breakout - Agil/EntityFactory.cpp"
#include "../Breakout - Agil/ComponentTable.h"
#include "../Breakout - Agil/ComponentTable.cpp"
#include "../Breakout - Agil/SoundSystem.h"
#include "../Breakout - Agil/SoundSystem.cpp"
#include "../Breakout - Agil/EventManager.h"
#include "../Breakout - Agil/EventManager.cpp"
#include "../Breakout - Agil/System.cpp"
#include "../Breakout - Agil/System.h"
#include "../Breakout - Agil/SoundCollisionComponent.h"
#include "../Breakout - Agil/Event.h"
#include "../Breakout - Agil/Event.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NativeTests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(StartupSoundSystem)
		{
			Assert::AreEqual(SoundEngine::GetInstance()->Initialize(), true);
		}
		TEST_METHOD(LoadSoundFile)
		{
			SoundEngine::GetInstance()->Initialize();
			unsigned int ID;
			Assert::AreEqual(SoundEngine::GetInstance()->LoadSoundToMemory("TestSound.wav", ID), true);
		}
		TEST_METHOD(LoadSameSoundFileTwice)
		{
			SoundEngine::GetInstance()->Initialize();
			unsigned int ID;
			SoundEngine::GetInstance()->LoadSoundToMemory("TestSound2.wav", ID);

			Assert::AreEqual(SoundEngine::GetInstance()->LoadSoundToMemory("TestSound2.wav", ID), true);
		}
		TEST_METHOD(LoadNonExistingSoundFile)
		{
			SoundEngine::GetInstance()->Initialize();
			unsigned int ID;

			Assert::AreEqual(SoundEngine::GetInstance()->LoadSoundToMemory("ThisDoesntExist.wav", ID), false);
		}
		TEST_METHOD(PlayOneSound)
		{
			SoundEngine::GetInstance()->Initialize();
			unsigned int ID;
			SoundEngine::GetInstance()->LoadSoundToMemory("TestSound.wav", ID);
			bool pPlaySoundWorked = SoundEngine::GetInstance()->PlaySound(ID);

			int a = 0;
			while (a < 7500000)
			{
				SoundEngine::GetInstance()->Update();
				a++;
			}
			

			Assert::AreEqual(pPlaySoundWorked, true);
		}
		TEST_METHOD(PlayTwoSoundsAtTheSameTime)
		{
			SoundEngine::GetInstance()->Initialize();
			unsigned int ID;
			SoundEngine::GetInstance()->LoadSoundToMemory("TestSound.wav", ID);
			bool pPlaySoundWorked = SoundEngine::GetInstance()->PlaySound(ID);

			int a = 0;
			while (a < 10000000)
			{
				SoundEngine::GetInstance()->Update();
				a++;
				if (a == 3500000)
				{
					pPlaySoundWorked = pPlaySoundWorked && SoundEngine::GetInstance()->PlaySound(ID);
				}
			}
			Assert::AreEqual(pPlaySoundWorked, true);
		}
		TEST_METHOD(CreateAndSaveSoundComponent)
		{
			SoundEngine::GetInstance()->Initialize();
			unsigned int ID;
			SoundEngine::GetInstance()->LoadSoundToMemory("TestSound2.wav", ID);

			SoundCollisionComponent* tSoundColl = new SoundCollisionComponent();
			tSoundColl->SoundID = ID;
			EntityFactory::EntityBlueprint tSoundCollBluePrint;
			tSoundCollBluePrint[SoundCollisionType] = tSoundColl;
			EntityFactory::GetInstance()->RegisterEntityTemplate("SoundCollTest", tSoundCollBluePrint);


			EntityID tNewID = EntityFactory::GetInstance()->CreateEntity("SoundCollTest");

			Assert::AreEqual(GetComponent<SoundCollisionComponent>(tNewID)->SoundID, ID);
		}
		TEST_METHOD(PlaySoundFromSoundComponent)
		{
			SoundEngine::GetInstance()->Initialize();
			unsigned int ID;
			SoundEngine::GetInstance()->LoadSoundToMemory("TestSound2.wav", ID);

			SoundCollisionComponent* tSoundColl = new SoundCollisionComponent();
			tSoundColl->SoundID = ID;
			EntityFactory::EntityBlueprint tSoundCollBluePrint;
			tSoundCollBluePrint[SoundCollisionType] = tSoundColl;
			EntityFactory::GetInstance()->RegisterEntityTemplate("SoundCollTest2", tSoundCollBluePrint);


			EntityID tNewID = EntityFactory::GetInstance()->CreateEntity("SoundCollTest2");

			bool pPlaySoundWorked = SoundEngine::GetInstance()->PlaySound(GetComponent<SoundCollisionComponent>(tNewID)->SoundID);

			int a = 0;
			while (a < 7500000)
			{
				SoundEngine::GetInstance()->Update();
				a++;
			}
			Assert::AreEqual(pPlaySoundWorked, true);
		}		
		TEST_METHOD(PlaySoundFromEvent)
		{;


			SoundSystem* tSoundSys = new SoundSystem();
			tSoundSys->Initialize();
			unsigned int ID;
			SoundEngine::GetInstance()->LoadSoundToMemory("TestSound.wav", ID);
			EventManager::Payload tPayload;
			unsigned int* tIDptr = new unsigned int();
			*tIDptr = ID;
			tPayload["SoundID"] = tIDptr;

			EventManager::GetInstance()->BroadcastEvent("Sound", tPayload);
			int a = 0;
			while (a < 7500000)
			{
				SoundEngine::GetInstance()->Update();
				a++;
			}

		}


	};
	TEST_CLASS(UnitTest2)
	{
		TEST_METHOD(MenyTester)
		{

		}
	};
}