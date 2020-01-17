/******************************************************************************/
/*!
\file   Level2.h
\author David Ly and Juyong Jeong
\par    email: jeykop14\@digipen.edu
\par    GAM150 demo
\date   2018/03/29

This level demonstrates how to create your own BaseObject class by deriving
from the engine's Object class. In addition, it also shows how you can add your
own custom Physics logic to enable you full access to Box2D physics. This is
only necessary if you plan to have more than basic collision and physics in your
game.
*/
/******************************************************************************/
#pragma once
#include "engine\State.h"
#include "CustomBaseObject.h"

class Level2 : public State
{
	friend class Game;

protected:

	Level2() : State() {};
	~Level2() override {};

	// Derived initialize function
	void Initialize() override;
	// Derived Update function
	void Update(float dt) override;
	// Derived Close function
	void Close() override;

private:

	// Objects which contains custom physics
	CustomBaseObject ball, wall, text;
};

