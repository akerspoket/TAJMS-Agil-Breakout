#include <iostream>
#include "Game1.h"
#include "EntityFactory.h"
#include "PhysicComponent.h"
#include "TransformComponent.h"
#include "StorageShelf.h"


using namespace std;

Game1 gGame;

int main()
{
	bool tNoError = gGame.Initialize();

	//TODO :: remove this is only test
	EntityFactory* tEntityFac = tEntityFac->GetInstance();
	PhysicComponent* tPhys = new PhysicComponent();
	TransformComponent* tTrans = new TransformComponent();

	tPhys->mIsSphere = true;
	tTrans->mPosition[0] = 1;
	tTrans->mPosition[1] = 2;
	tTrans->mPosition[2] = 3;

	tTrans->mRotation[0] = 4;
	tTrans->mRotation[1] = 5;
	tTrans->mRotation[2] = 6;

	EntityFactory::EntityBlueprint tNewBlueprint;
	tNewBlueprint[PhysicType] = tPhys;
	tNewBlueprint[TransformType] = tTrans;

	tEntityFac->RegisterEntityTemplate("Boll", tNewBlueprint);

	EntityID tID = tEntityFac->CreateEntity("Boll");

	tPhys = GetComponent<PhysicComponent>(tID);
	tTrans = GetComponent<TransformComponent>(tID);

	/*PhysicComponent* tPhys = GetComponent<PhysicComponent>(2);
	tPhys->mIsSphere = true;
	tPhys = GetComponent<PhysicComponent>(0);
	tPhys = GetComponent<PhysicComponent>(2);
*/


	if (tNoError)
		gGame.Run();


	return 0;
}

