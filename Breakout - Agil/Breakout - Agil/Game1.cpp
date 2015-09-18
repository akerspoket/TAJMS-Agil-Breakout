#include "Game1.h"
#include "PhysicSystem.h"
#include "InputSystem.h"
#include "RenderSystem.h"
#include "TriggerSystem.h"
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
	InputSystem* tInput = new InputSystem();
	tInput->Initialize();
	mSystems.push_back(tInput);
	
	PhysicSystem* tPhysics = new PhysicSystem();
	tPhysics->Initialize();
	mSystems.push_back(tPhysics);

	RenderSystem* tRender = new RenderSystem();
	tRender->Initialize();
	mSystems.push_back(tRender);

	TriggerSystem* tTrigger = new TriggerSystem();
	tTrigger->Initialize();
	mSystems.push_back(tTrigger);


	mGraphicsEngine = new GraphicsEngine();
	mGraphicsEngine->InitD3D(GetActiveWindow());
	mGraphicsEngine->InitPipeline();
	mGraphicsEngine->InitGraphics();

	
	return true;
}

void Game1::Run()
{
	double tDeltaTimeMilli = 17; //global? or sent in func

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
			sys->Update(tDeltaTimeMilli);
		}

	}
}

void Game1::Destroy()
{

}
