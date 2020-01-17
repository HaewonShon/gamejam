#pragma once
/******************************************************************************/
/*!
\file   Level3.h
\author David Ly and Juyong Jeong
\par    email: dly\@digipen.edu
\par    GAM150 demo
\par	v0
\date   2018/04/04

Containing examples how to use engine
*/
/******************************************************************************/
#pragma once
#include "engine\State.h"
#include "engine\Object.h"

class Level3 : public State
{
	friend class Game;

protected:

	Level3() : State() {};
	~Level3() override {};

	// Derived initialize function
	void Initialize() override;
	// Derived Update function
	void Update(float dt) override;
	// Derived Close function
	void Close() override;

private:

	void SetIntroTexts();

	Object electricity, explosion, snow, fire;
	Object introTexts[4];
    Object emitterController;
};

