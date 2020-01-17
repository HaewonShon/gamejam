/******************************************************************************/
/*!
\file   DemoControlEmitters.h
\author Hun Yang
\par    email: hun.yang8456@gmail.com
\par    GAM150 demo
\date   2019/03/26

This is component that control emitters in Level 3.

*/
/******************************************************************************/
#pragma once
#include "Component.h"

class Object;
class DemoControlEmitters : public Component
{
public:
    DemoControlEmitters();
    ~DemoControlEmitters();
    virtual void Initialize() override;
    virtual void Update(float dt) override;
    Object* electricity;
    Object* explosion;
    Object* snow;
    Object* fire;
private:
    bool electricitytoggle, snowToggle, fireToggle, changeToggle;
    float radian;
};
