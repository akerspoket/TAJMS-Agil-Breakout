#include "SoundSystem.h"
#include "EventManager.h"


SoundSystem::SoundSystem()
{
	mSoundEngine = mSoundEngine->GetInstance();

	if (!mSoundEngine->Initialize())
	{
		cout << "Couldn't initialize SoundEngine" << endl;
	}

}

SoundSystem::SoundSystem(string pName) :System(pName)
{
	mSoundEngine = mSoundEngine->GetInstance();

	if (!mSoundEngine->Initialize())
	{
		cout << "Couldn't initialize SoundEngine" << endl;
	}
}


SoundSystem::~SoundSystem()
{
}

void SoundSystem::Initialize()
{
	mEventManager = mEventManager->GetInstance();
	mEventManager->Subscribe("Sound", this);
	////LinuxSOundTest=)
#ifdef LinuxSound
	unsigned int tID;
	mSoundEngine->LoadSoundToMemory("TestSound.wav", tID);
	mSoundEngine->PlaySound(tID);
#endif
}

void SoundSystem::Start()
{
}

void SoundSystem::Update(double pDeltaTime)
{
	mSoundEngine->Update();
}

void SoundSystem::Pause()
{
}

void SoundSystem::Stop()
{
}

void SoundSystem::OnEvent(Event * pEvent)
{
	string pEventID = pEvent->mID;

	if (pEventID == "Sound")
	{
		//get sound ID
		unsigned int tSoundID = *(unsigned int*)pEvent->mPayload["SoundID"];
		
		//play sound	

#ifdef _DEBUG
		 bool tResult = mSoundEngine->PlaySound(tSoundID);
		if (!tResult)
		{
			cout << "Couldnt not play sound" << tSoundID << endl;
		}
#else
		mSoundEngine->PlaySound(tSoundID);
#endif
		
	}
}
