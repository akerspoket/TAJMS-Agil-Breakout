#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Breakout - Agil/SoundEngine.h"
#include "../Breakout - Agil/SoundEngine.cpp"
#include "../Breakout - Agil/Constants.h"


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
					bool pPlaySoundWorked = SoundEngine::GetInstance()->PlaySound(ID);
				}
			}
		}


	};
}