#pragma once
enum ButtonName
{
	/////MenyMeny
	MainStart,
	MainOption,
	MainHighscore,
	MainTutorial,
	MainQuit,
	//////PauseMeny
	PauseResume,
	PauseRestartLevel,
	PauseQuitToMainMenu,
	/////DeathMenu
	DeathRestartLevel,
	DeathQuitToMainMenu,

};
struct MenyButtonComponent
{
	MenyButtonComponent()
	{
		mButtonName = MainStart;
	}
	ButtonName mButtonName;
};
