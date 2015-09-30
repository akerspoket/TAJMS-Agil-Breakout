#pragma once
#include "fmod.hpp"
#include "fmod_errors.h"
#include <map>

//using namespace FMOD;
using namespace std;
#define ERROR_SOUND 0

class SoundEngine
{
public:
	static SoundEngine* GetInstance();
	bool LoadSoundToMemory(string pFileToLoad, unsigned int &pSoundID);
	bool PlaySound(unsigned int pSoundID);
	bool Initialize();
	void Update();

private:
	static SoundEngine* mSingleton;
	SoundEngine();
	~SoundEngine();
	bool FMODFail(FMOD_RESULT pResult);
	typedef map<unsigned int, FMOD::Sound*> SoundMap;
	SoundMap mSoundMap;

	//Interface
	FMOD::System *system;
	
	unsigned int version;
	int numDrivers;
	FMOD_SPEAKERMODE speakerMode;
	FMOD_CAPS caps;
	char name[256];

};

