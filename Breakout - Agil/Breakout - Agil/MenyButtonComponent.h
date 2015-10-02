#pragma once
enum ButtonName
{
	/////MenyMeny
	Start,
	Option,
	Highscore,
	Tutorial,
	Quit,
	//////PauseMeny
	Resume,
	PauseQuit,

};
struct MenyButtonComponent
{
	MenyButtonComponent()
	{
		mButtonName = Start;
	}
	ButtonName mButtonName;
};
