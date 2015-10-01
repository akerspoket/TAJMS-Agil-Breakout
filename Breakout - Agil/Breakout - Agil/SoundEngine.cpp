#include "SoundEngine.h"


#include <iostream>

SoundEngine* SoundEngine::mSingleton = nullptr;

SoundEngine* SoundEngine::GetInstance()
{
	if (mSingleton == nullptr)
	{
		mSingleton = new SoundEngine();
	}
	return mSingleton;
}

SoundEngine::SoundEngine()
{
	mSoundMap = map<unsigned int, FMOD::Sound*>();
}


SoundEngine::~SoundEngine()
{
}

bool SoundEngine::Initialize()
{
	FMOD_RESULT tResult;
	// Create FMOD interface object
	tResult = FMOD::System_Create(&system);
	if (FMODFail(tResult))
	{
		return false;
	}
		
	//check version
	tResult = system->getVersion(&version);

	if (version < FMOD_VERSION)
	{
		cout << "Error! You are using an old version of FMOD " << version << ". This program requires " << FMOD_VERSION << endl;
	}

	if (FMODFail(tResult))
	{
		return false;
	}

	// Get number of sound cards 
	tResult = system->getNumDrivers(&numDrivers);
	if (FMODFail(tResult))
	{
		return false;
	}

	// No sound cards (disable sound)
	if (numDrivers == 0)
	{
		tResult = system->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
		if (FMODFail(tResult))
		{
			return false;
		}
	}
	else
	{
		// Get the capabilities of the default (0) sound card
		tResult = system->getDriverCaps(0, &caps, 0, &speakerMode);
		if (FMODFail(tResult))
		{
			return false;
		}

		// Set the speaker mode to match that in Control Panel
		tResult = system->setSpeakerMode(speakerMode);
		if (FMODFail(tResult))
		{
			return false;
		}

		// Increase buffer size if user has Acceleration slider set to off
		if (caps & FMOD_CAPS_HARDWARE_EMULATED)
		{
			tResult = system->setDSPBufferSize(1024, 10);
			if (FMODFail(tResult))
			{
				return false;
			}
		}

		// Get name of driver
		tResult = system->getDriverInfo(0, name, 256, 0);
		if (FMODFail(tResult))
		{
			return false;
		}

		// SigmaTel sound devices crackle for some reason if the format is PCM 16-bit.
		// PCM floating point output seems to solve it.
		if (strstr(name, "SigmaTel"))
		{
			tResult = system->setSoftwareFormat(48000, FMOD_SOUND_FORMAT_PCMFLOAT, 0, 0, FMOD_DSP_RESAMPLER_LINEAR);
			if (FMODFail(tResult))
			{
				return false;
			}
		}

	}

	// Initialise FMOD
	tResult = system->init(100, FMOD_INIT_NORMAL, 0);

	// If the selected speaker mode isn't supported by this sound card, switch it back to stereo
	if (tResult == FMOD_ERR_OUTPUT_CREATEBUFFER)
	{
		tResult = system->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
		if (FMODFail(tResult))
		{
			return false;
		}

		tResult = system->init(100, FMOD_INIT_NORMAL, 0);
	}
	if (FMODFail(tResult))
	{
		return false;
	}



	return true;
}

bool SoundEngine::FMODFail(FMOD_RESULT pResult)
{
	if (pResult != FMOD_OK)
	{
		cout << "FMOD Error - " << pResult << " - " << FMOD_ErrorString(pResult) << endl;
		return true;
	}
	return false;
}


bool SoundEngine::LoadSoundToMemory(string pFileToLoad, unsigned int &pSoundID)
{
	FMOD_RESULT tResult;

	hash<string> tHash;
	unsigned int tID = tHash(pFileToLoad);

	SoundMap::iterator tIter = mSoundMap.find(tID);

	//if we got the sound loaded we return the ID from map
	if (tIter != mSoundMap.end())
	{
		pSoundID = tIter->first;

		return true;
	}
	
	//if not already loaded, we try load from file
	FMOD::Sound *tAudio;
	string pFullPathName = "../Sounds/" + pFileToLoad;
	tResult = system->createSound(pFullPathName.c_str(), FMOD_DEFAULT, 0, &tAudio);
	if (FMODFail(tResult))
	{
		return false;
	}

	//if loaded is successful, we save the ID and string
	mSoundMap[tID] = tAudio;
	pSoundID = tID;

	return true;
}

bool SoundEngine::PlaySound(unsigned int pSoundID)
{
	FMOD_RESULT tResult;

	FMOD::Sound* tAudio = mSoundMap[pSoundID];
	//check if a bad ID
	if (tAudio == nullptr)
	{
		return false;
	}

	//play sound
	tResult = system->playSound(FMOD_CHANNEL_FREE, tAudio, false, 0);
	if (FMODFail(tResult))
	{
		return false;
	}

	return true;
}

void SoundEngine::Update()
{
	FMOD_RESULT tResult;

	tResult = system->update();
	FMODFail(tResult);

}