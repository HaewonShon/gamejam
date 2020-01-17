#pragma once
/******************************************************************************/
/*!
\file   Level9.h
\author Hun Yang
\par    email: hun.yang8456@gmail.com
\par    GAM150 demo
\par	v0
\date   2019/04/27

Conaining examples how to use engine
*/
/******************************************************************************/
#pragma once
#include "engine\State.h"
#include "CustomBaseObject.h"


class LevelTopdown : public State
{
    friend class Game;

protected:

    LevelTopdown() : State() {};
    ~LevelTopdown() override {};

    // Derived initialize function
    void Initialize() override;
    // Derived Update function
    void Update(float dt) override;
    // Derived Close function
    void Close() override;
private:
private:
    CustomBaseObject player;
    CustomBaseObject enemySpawner;
    CustomBaseObject gameOverScreen;
    CustomBaseObject score;
};

