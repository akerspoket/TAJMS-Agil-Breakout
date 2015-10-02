#pragma once


static enum GameState
{
	MenuScreen,
	GameScreen,
	DeathScreen,
	PauseScreen,
};

class GameStateClass
{
public:
	static GameStateClass* GetInstance();
	GameState GetGameState() { return gGameState; }
	void SetGameState(GameState pState) { gGameState = pState; }

private:
	static GameStateClass* mSingleton;
	GameStateClass();
	~GameStateClass();
	GameState gGameState;
};

