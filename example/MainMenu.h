/******************************************************************************/
/*!
\file   MainMenu.h
\author David Ly and Juyong Jeong
\par    email: dly\@digipen.edu
\par    GAM150 demo
\par	v0
\date   2018/03/11

Conaining examples how to use engine
*/
/******************************************************************************/
#pragma once
#include "engine\State.h"
#include "engine\Object.h"
#include "CustomBaseObject.h"

class DemoUIButton;
class MainMenu : public State
{
	friend class Game;

protected:

	MainMenu() : State() {};
	~MainMenu() override {};

	// Derived initialize function
	void Initialize() override;
	// Derived Update function
	void Update(float dt) override;
	// Derived Close function
	void Close() override;

private:

    CustomBaseObject titleText;
    CustomBaseObject background;
    CustomBaseObject basicText, topdownText, platformerText;
    CustomBaseObject basicStartButton, topdownStartButton, platformerStartButton;
    CustomBaseObject exitButton;
};

