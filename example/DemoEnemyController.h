/******************************************************************************/
/*!
\file   DemoEnemyController.h
\author Hun Yang
\par    email: hun.yang8456@gmail.com
\par    GAM150 demo
\date   2019/04/28

Enemy controller which move based on platformer controller logic
*/
/******************************************************************************/
#pragma once
#include "DemoPlatformerController.h"

class DemoEnemyController : public DemoPlatformerController
{
public:
    DemoEnemyController();
    ~DemoEnemyController();
    virtual void Initialize() override;
    virtual void Update(float dt) override;
private:
    // change image's flip based on moving direction
    void        animationUpdate();
public:
    float               mMovingDistance;    // distance that enemy can move
private:
    float               mMinPositionX;      // minimun x position to move
    float               mMaxPositionX;      // maximun x position to move
};
