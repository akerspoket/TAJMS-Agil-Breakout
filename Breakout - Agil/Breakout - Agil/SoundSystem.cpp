#include "SoundSystem.h"
#include "SoundEngine.h"


SoundSystem::SoundSystem()
{
	SoundEngine* tSoundEngine = tSoundEngine->GetInstance();

	if (!tSoundEngine->Initialize())
	{
		cout << "Couldn't initialize SoundEngine" << endl;
	}
}


SoundSystem::~SoundSystem()
{
}
