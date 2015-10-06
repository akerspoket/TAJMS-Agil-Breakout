#include "AttachSystem.h"

#include "EventManager.h"
#include "EntityManager.h"
#include "ComponentTable.h"
#include "StorageShelf.h"

#include "AttachedComponent.h"
#include "TransformComponent.h"
#include "GameState.h"
#include "LabelComponent.h"





AttachSystem::AttachSystem()
{
}

AttachSystem::AttachSystem(string pName) :System(pName)
{

}

AttachSystem::~AttachSystem()
{
}

void AttachSystem::Initialize()
{
	mEventManager = mEventManager->GetInstance();
	mEventManager->Subscribe("MenuPointerAttachment", this);
}
void AttachSystem::Start(){}
void AttachSystem::Update(double pDeltaTime)
{
	EntityManager* tEntManager = tEntManager->GetInstance();
	ComponentTable* tCompTable = tCompTable->GetInstance();
	int tMaxEnt = tEntManager->GetLastEntity();





	for (int i = 0; i < tMaxEnt; i++)
	{
		//Ensure that relevant components exist
		short tFlags = TransformType | AttachedType;
		if (tCompTable->HasComponent(i, tFlags))
		{
			AttachedComponent* tAtt = GetComponent<AttachedComponent>(i);
			TransformComponent* tAttTrans = GetComponent<TransformComponent>(i);

			vec3 attachedTo_Pos = GetComponent<TransformComponent>(tAtt->attachedTo)->mPosition; //position which attached entity is attached to
			tAttTrans->mPosition = attachedTo_Pos + tAtt->relPos;
		}
	}

	
}
void AttachSystem::Pause(){}
void AttachSystem::Stop(){}
void AttachSystem::OnEvent(Event* pEvent)
{
	//MenuPointerAttachment

	EntityManager* tEntMan = tEntMan->GetInstance();
	ComponentTable* tCompTable = tCompTable->GetInstance();
	int tMaxEnt = tEntMan->GetLastEntity();

	string pEventID = pEvent->mID;

	if (pEventID == "MenuPointerAttachment")
	{
		for (int i = 0; i < tMaxEnt; i++)
		{
			if (tCompTable->HasComponent(i, AttachedType | LabelType))
			{

				if (GetComponent<LabelComponent>(i)->mLabel==Label::MenuPointer)
				{
					AttachedComponent* tAttachedComp = GetComponent<AttachedComponent>(i);
					int tMenyButtonID;
					tMenyButtonID = *(int*)pEvent->mPayload["MenuButtonID"];
					tAttachedComp->attachedTo = tMenyButtonID;
				}


				
			}
		}
	}
}
