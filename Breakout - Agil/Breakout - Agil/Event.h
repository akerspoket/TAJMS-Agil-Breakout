#pragma once
#include <string>
#include <unordered_map>

using namespace std;

class Event
{
public:
	Event();
	Event(string pName);
	~Event();

	string mID;
	unordered_map<string, void*> mPayload;
};

