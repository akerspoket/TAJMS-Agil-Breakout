#pragma once
#include <vector>
using namespace std;
struct UserCmd
{
	vector<char>mKeysPressed;
	float mXMove;//for the mouse
	float mYMove;//for the mouse
	bool mRightArrowPressed;
	bool mLeftArrowPressed;
	bool mUpArrowPressed;
	bool mDownArrowPressed;
	bool mSpaceButtonPressed;
	bool mEnterButtonPressed;
};

static UserCmd gUserCmd;
static UserCmd gLastUserCmd;