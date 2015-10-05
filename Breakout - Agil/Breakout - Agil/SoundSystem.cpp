#include "SoundSystem.h"
#include "EventManager.h"
#include "StorageShelf.h"
#include "ComponentTable.h"
#include "SoundCollisionComponent.h"

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
	mEventManager->Subscribe("Collision", this);
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

	if (pEventID == "Collision")
	{
		if (ComponentTable::GetInstance()->HasComponent(*(EntityID*)pEvent->mPayload["ID1"], SoundCollisionType))
		{
			unsigned int* tSoundIDptr = new unsigned int();
			*tSoundIDptr = GetComponent<SoundCollisionComponent>(*(EntityID*)pEvent->mPayload["ID1"])->SoundID;
			EventManager::Payload tPayload;
			tPayload["SoundID"] = tSoundIDptr;
			mEventManager->BroadcastEvent("Sound", tPayload);
		}
		if (ComponentTable::GetInstance()->HasComponent(*(EntityID*)pEvent->mPayload["ID2"], SoundCollisionType))
		{
			unsigned int* tSoundIDptr = new unsigned int();
			*tSoundIDptr = GetComponent<SoundCollisionComponent>(*(EntityID*)pEvent->mPayload["ID2"])->SoundID;
			EventManager::Payload tPayload;
			tPayload["SoundID"] = tSoundIDptr;
			mEventManager->BroadcastEvent("Sound", tPayload);
		}
	}
}
