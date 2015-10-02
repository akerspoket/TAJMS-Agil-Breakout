#include "MenuSystem.h"
#include "GameState.h"
#include "EntityManager.h"
#include "ComponentTable.h"
#include "StorageShelf.h"


MenuSystem::MenuSystem()
{
}

MenuSystem::MenuSystem(string pName) : System(pName)
{
}


MenuSystem::~MenuSystem()
{
}

void MenuSystem::Initialize()
{
}

void MenuSystem::Start()
{
}

void MenuSystem::CheckMenuInput()
{
	//gUserCmd
}

void MenuSystem::Update(double pDeltaTime)
{
	switch (GameStateClass::GetInstance()->GetGameState())
	{
	case MenuScreen:
		//check input if we're in menu
		CheckMenuInput();
		break;
	case GameScreen:
		break;
	case DeathScreen:
		break;
	case PauseScreen:
		break;
	default:
		break;
	}


}

void MenuSystem::Pause()
{
}

void MenuSystem::Stop()
{
}

void MenuSystem::OnEvent(Event * pEvent)
{
	//change here on input
}
