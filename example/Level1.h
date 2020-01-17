/******************************************************************************/
/*!
\file   Level1.h
\author David Ly and Juyong Jeong
\par    email: dly\@digipen.edu
\par    GAM150 demo
\par	v0
\date   2018/03/11

Example that shows simple collision response (reflection) between dynamic vs
static and dynamic vs dynamic objects.
*/
/******************************************************************************/
#pragma once
#include "engine\State.h"
#include "engine\Object.h"
#include <vector>

class Level1 : public State
{
	friend class Game;

protected:

	Level1() : State() {};
	~Level1() override {};

	// Derived initialize function
	void Initialize() override;
	// Derived Update function
	void Update(float dt) override;
	// Derived Close function
	void Close() override;

private:

	std::vector<Object*> m_dynamicList;

	void SetIntroTexts();

	Object& BuildAndRegisterWall(Object &wall, const char *name, float positionX, float positionY, float scaleX, float scaleY);
	Object& BuildAndRegisterBody(Object &body, const char *name, float positionX, float positionY, Physics::BodyShape shape);

	// Objects
	Object	blackBall, blueBall, redBall, box, bottom, top, left, right;
	Object	introTexts[6];
};

