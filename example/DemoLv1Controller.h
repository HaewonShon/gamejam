/******************************************************************************/
/*!
\file   DemoLv1Controller.h
\author Hun Yang
\par    email: hun.yang8456@gmail.com
\par    GAM150 demo
\date   2019/03/26

This is controller for Level4 Demo.

*****YOU CANNOT MODIFY THIS FILE!!*****
*/
/******************************************************************************/
#pragma once
#include "Component.h"

class DemoLv1Controller : public Component
{
public:
    DemoLv1Controller();
    ~DemoLv1Controller();
    virtual void Initialize() override;
    virtual void Update(float dt) override;
private:
    float   GetRandomFloat();
    void    CollisionResponse();
public:
    Object* redBall;
    Object* blueBall;
    Object* blackBall;
    Object* collisionText;
private:
    bool toggle;
};
