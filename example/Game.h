/******************************************************************************/
/*!
\file   Game.h
\author David Ly and Juyong Jeong
\par    email: dly\@digipen.edu
\par    GAM150 demo
\par	v0
\date   2018/03/11

Game will only handle the changes of the game states (Level switching)
ie. Main Menu, Levels, Pause, etc.
No game play logic should be added here.
*/
/******************************************************************************/

#pragma once

// Level headers
#include "MainMenu.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include "PauseState.h"
#include "LevelTopdown.h"
#include "LevelPlatformer.h"

//This is the list of levels the game has. When adding a new level(state)
//add it to this list. They are tagged with LV_ to enable better autocomplete 
typedef enum
{
	LV_MainMenu = 0,
	LV_Level1,
	LV_Level2,
	LV_Level3,
	LV_Level4,
    LV_LevelTopdown,
    LV_LevelPlatformer,

	LV_Pause,
	//etc.

	LV_NUM_LEVELS
}Level_ID;

class StateManager;

class Game
{
	friend class Application;

	StateManager *m_stateManager = nullptr;

public:

	Game();
	~Game();

	void	RegisterState(State* state);
	void	SetFirstState(State* state);
	State*	GetCurrentState();

	void	Quit();
	void	Change(unsigned stateId);

	bool	Initialize();
	void	Update(float dt);
	void	Close();

	void	RegisterPauseState(State *state);
	void	Pause();
	void	Resume();
	void	Restart();
	bool	IsQuit();
    bool    IsRestart();
        
private:
	
	// All the level(state) declarations are here
	MainMenu	mainMenu;
	Level1		level1;
	Level2		level2;
	Level3		level3;
	Level4		level4;
    LevelTopdown levelTopdown;
    LevelPlatformer      levelPlatformer;
	PauseState	pauseLevel;

public:
	
	static constexpr int SCREEN_WIDTH = 1280, SCREEN_HEIGHT = 720;
	int	m_width = 0, m_height = 0;

	Game(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(const Game&) = delete;
	Game& operator=(Game&&) = delete;

};