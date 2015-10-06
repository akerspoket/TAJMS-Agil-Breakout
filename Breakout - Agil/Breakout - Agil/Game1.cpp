#include "Game1.h"
#include "PhysicSystem.h"
#include "InputSystem.h"
#include "AttachSystem.h"
#include "RenderSystem.h"
#include "TriggerSystem.h"
#include "SoundSystem.h"
#include "VelocitySystem.h"
#include "MenuSystem.h"
#include "StorageShelf.h"
#include "PhysicComponent.h"
#include "ScoreSystem.h"
#include "GameState.h"
#include "PowerUpSystem.h"

Game1::Game1()
{
}


Game1::~Game1()
{
}

bool Game1::Initialize(SDL_Window* pWin)
{
	InputSystem* tInput = new InputSystem("InputSystem");
	VelocitySystem* tVel = new VelocitySystem("VelocitySystem");
	AttachSystem* tAtt = new AttachSystem("AttachSystem");
	PhysicSystem* tPhysics = new PhysicSystem("PhysicSystem");
	RenderSystem* tRender = new RenderSystem("RenderSystem");
	TriggerSystem* tTrigger = new TriggerSystem("TriggerSystem");
	SoundSystem* tSound = new SoundSystem("SoundSystem");
	ScoreSystem* tScore = new ScoreSystem("ScoreSystem");
	MenuSystem* tMenu = new MenuSystem("MenuSystem");
	PowerUpSystem* tPowerUps = new PowerUpSystem("PowerUpSystem");
	
	tRender->Initialize();
	tRender->Initialize(pWin);
	tInput->Initialize();
	tVel->Initialize();
	tAtt->Initialize();
	tPhysics->Initialize();
	tTrigger->Initialize();
	tSound->Initialize();
	tScore->Initialize();
	tMenu->Initialize();
	tPowerUps->Initialize();

	//set systems to game here
	mSystems.push_back(tInput);
	mSystems.push_back(tVel);
	mSystems.push_back(tPhysics);
	mSystems.push_back(tTrigger);
	mSystems.push_back(tAtt);
	mSystems.push_back(tSound);
	mSystems.push_back(tScore);
	mSystems.push_back(tPowerUps);
	mSystems.push_back(tMenu);
	mSystems.push_back(tRender);
	
	GameStateClass::GetInstance()->SetGameState(GameState::MenuScreen);



	
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

		//update systems based on gamestate
		for (auto sys : mSystems)
		{
			sys->Update(tDeltaTimeSecond);
		}

	}
}

void Game1::Destroy()
{

}
