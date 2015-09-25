#include "System.h"
#include "EventManager.h"

System::System()
{
	mSystemName = "NoSystemName";
}

System::System(string pName)
{
	mSystemName = pName;
}

System::~System()
{

}

string System::GetName()
{
	return mSystemName;
}
