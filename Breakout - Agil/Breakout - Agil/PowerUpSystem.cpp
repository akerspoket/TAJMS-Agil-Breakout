#include "PowerUpSystem.h"
#include "EventManager.h"
#include "EntityManager.h"
#include "ComponentTable.h"
#include "StorageShelf.h"
#include "VelocityComponent.h"
#include "PowerUpComponent.h"

PowerUpSystem::PowerUpSystem()
{
}

PowerUpSystem::PowerUpSystem(string pName):System(pName)
{

}


PowerUpSystem::~PowerUpSystem()
{
}

void PowerUpSystem::Initialize(){}
void PowerUpSystem::Start(){}
void PowerUpSystem::Update(double pDeltaTime)
{

}
void PowerUpSystem::Pause(){}
void PowerUpSystem::Stop(){}
void PowerUpSystem::OnEvent(Event* pEvent){}