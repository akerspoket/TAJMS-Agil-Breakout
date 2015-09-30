#include "Game1.h"
#include "PhysicSystem.h"
#include "InputSystem.h"
#include "RenderSystem.h"
#include "TriggerSystem.h"
#include "SoundSystem.h"
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
	tInput->Initialize();
	mSystems.push_back(tInput);
	
	PhysicSystem* tPhysics = new PhysicSystem("PhysicSystem");
	tPhysics->Initialize();
	mSystems.push_back(tPhysics);

	RenderSystem* tRender = new RenderSystem("RenderSystem");
	tRender->Initialize();
	mSystems.push_back(tRender);

	TriggerSystem* tTrigger = new TriggerSystem("TriggerSystem");
	tTrigger->Initialize();
	mSystems.push_back(tTrigger);

	SoundSystem* tSound = new SoundSystem("SoundSystem");
	tSound->Initialize();
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
		for each (System* sys in mSystems)
		{
			sys->Update(tDeltaTimeSecond);
		}

	}
}

void Game1::Destroy()
{

}
