#pragma once
/******************************************************************************/
/*!
\file   Level9.h
\author Hun Yang
\par    email: hun.yang8456@gmail.com
\par    GAM150 demo
\par	v0
\date   2019/04/15

Containing examples how to use engine
*/
/******************************************************************************/
#pragma once
#include "engine\State.h"
#include "CustomBaseObject.h"



class LevelPlatformer : public State
{
    friend class Game;

protected:

    LevelPlatformer() : State() {};
    ~LevelPlatformer() override {};

    // Derived initialize function
    void Initialize() override;
    // Derived Update function
    void Update(float dt) override;
    // Derived Close function
    void Close() override;
private:
private:
    CustomBaseObject player;
    CustomBaseObject cameraController;
    CustomBaseObject platform1, platform2, platform3, platform4, platform5, platform6, platform7, platform8;
    CustomBaseObject stairPlatforms[5];
    CustomBaseObject bridge;
    CustomBaseObject checkPoint1, checkPoint2, checkPoint3, checkPoint4;
    CustomBaseObject spikes[9];
    CustomBaseObject damageTrap1;
    CustomBaseObject gameOverScreen;
    CustomBaseObject enemy1, enemy2;
    CustomBaseObject levelClear;
    CustomBaseObject item1, item2, item3;

    //b2Vec2              playerStartPosition;
};

