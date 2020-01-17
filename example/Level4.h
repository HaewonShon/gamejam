#pragma once
/******************************************************************************/
/*!
\file   Level4.h
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
#include "CustomBaseObject.h"

class Level4 : public State
{
	friend class Game;

protected:

	Level4() : State() {};
	~Level4() override {};

	// Derived initialize function
	void Initialize() override;
	// Derived Update function
	void Update(float dt) override;
	// Derived Close function
	void Close() override;

private:

	void SetIntroTexts();

	CustomBaseObject& BuildAndRegisterWall(CustomBaseObject &wall, const char *name, float positionX, float positionY, float scaleX, float scaleY);
	CustomBaseObject& BuildAndRegisterBody(CustomBaseObject &body, const char *name, float positionX, float positionY, CustomPhysics::BodyShape shape);

	// Objects
	CustomBaseObject	blackBall, blueBall, redBall, box, bottom, top, left, right;
	CustomBaseObject	introTexts[6];
};

