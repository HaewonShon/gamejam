/******************************************************************************/
/*!
\file   Turret.h
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
#include <Box2D/Common/b2Math.h>
#include "engine/Object.h"

class Turret : public Object
{
public:
    Turret();
    ~Turret();
    void OnShoot();
    void IncreaseRotation(int deltaRotationDegrees);
    b2Vec2 GetTipLocation();
    b2Vec2 GetVelocityVector() const;
    void Update(float dt) override;
private:
    int rotationDegrees;
    Object shootSfx;

    b2Vec2 GetNormalizedDirectionVector() const;
private:

    float bullet_diameter;
};
