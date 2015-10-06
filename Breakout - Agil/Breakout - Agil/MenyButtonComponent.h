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

enum ButtonMenuBelonging
{
	MainMenu,
	PauseMenu,
	DeathMenu,
};

struct MenyButtonComponent
{
	MenyButtonComponent()
	{
		mButtonBelong = MainMenu;
	}
	ButtonMenuBelonging mButtonBelong;
	ButtonName mButtonName;
};
