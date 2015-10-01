#include "Game1.h"
#include "PhysicSystem.h"
#include "InputSystem.h"
#include "RenderSystem.h"
#include "TriggerSystem.h"
#include "SoundSystem.h"
#include "VelocitySystem.h"
#include "StorageShelf.h"
#include "PhysicComponent.h"



Game1::Game1()
{
}


Game1::~Game1()
{
}

bool Game1::Initialize()
{
	InputSystem* tInput = new InputSystem("InputSystem");
	VelocitySystem* TVel = new VelocitySystem("VelocitySystem");
	PhysicSystem* tPhysics = new PhysicSystem("PhysicSystem");
	RenderSystem* tRender = new RenderSystem("RenderSystem");
	TriggerSystem* tTrigger = new TriggerSystem("TriggerSystem");
	SoundSystem* tSound = new SoundSystem("SoundSystem");
	
	
	tInput->Initialize();
	TVel->Initialize();
	tPhysics->Initialize();
	tRender->Initialize();
	tTrigger->Initialize();
	tSound->Initialize();
	

	mSystems.push_back(tInput);
	mSystems.push_back(TVel);
	mSystems.push_back(tPhysics);
	mSystems.push_back(tRender);
	mSystems.push_back(tTrigger);
	mSystems.push_back(tSound);
	

	
	return true;
}

void Game1::Run()
{
	double tDeltaTimeSecond = 0.017f; //global? or sent in func

	SDL_Event tEvent;

	while (true)
	{
		while (SDL_PollEvent(&tEvent))
		{
			switch (tEvent.type)
			{
				// do nothing... yet
			}
		}

		//mGraphicsEngine->RenderFrame();
		for (auto sys : mSystems)
		{
			sys->Update(tDeltaTimeSecond);
		}

	}
}

void Game1::Destroy()
{

}
