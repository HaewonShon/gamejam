/******************************************************************************/
/*!
\file   DemoLv4Controller.h
\author Hun Yang
\par    email: hun.yang8456@gmail.com
\par    GAM150 demo
\date   2019/03/26

This is almost same with Lv4Controller, 
but difference is this uses CustomBaseObject instead of Object.

*****YOU CANNOT MODIFY THIS FILE!!*****
*/
/******************************************************************************/
#pragma once
#include "Component.h"
#include <vector>

class CustomPhysics;
class CustomBaseObject;
class DemoLv4Controller : public Component
{
public:
    DemoLv4Controller();
    ~DemoLv4Controller();
    virtual void Initialize() override;
    virtual void Update(float dt) override;
private:
    float   GetRandomFloat();
    void    CollisionResponse();
public:
    CustomBaseObject* redBall;
    CustomBaseObject* blueBall;
    CustomBaseObject* blackBall;
    CustomBaseObject* collisionText;
    std::vector<CustomPhysics*>* physicsVector;
private:
    CustomBaseObject* customOwner;
    bool toggle;
};
