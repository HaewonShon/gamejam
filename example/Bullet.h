/******************************************************************************/
/*!
\file   Bullet.h
\author Jay Austria
\par    email: noyoucannot\@gmail.com
\par    GAM150 demo
\par	v0
\date   2018/03/28

Example that shows very simple dynamic object creation and handling of dynamic
objects, which is useful for short lived objects such as bullets.
*/
/******************************************************************************/
#pragma once
#include <SDL2/SDL.h>
#include "engine/Object.h"
#include "CustomBaseObject.h"

class Bullet : public Object
{
public:
    Bullet();
    SDL_Color GetBirthColor() const { return birthColor; }
    bool IsOffscreen() const;
    void Update(float dt) override;
private:
    SDL_Color birthColor;
};

class CustomBullet : public CustomBaseObject
{
public:
    CustomBullet();
    void Update(float dt) override;
private:
    virtual void Initialize() override;
public:
    float       mLifeCount;
private:
    float       mTimer;
};
