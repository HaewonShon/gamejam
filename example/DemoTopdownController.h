/******************************************************************************/
/*!
\file   DemoTopdownController.h
\author Hun Yang
\par    email: hun.yang8456@gmail.com
\par    GAM150 demo
\date   2019/04/30

basic topdown demo controller
*/
/******************************************************************************/
#pragma once
#include "Component.h"

enum class eDemoTopdownPlayerState
{
    Normal,
    Damaged,
    Dead,
    GameOver
};

struct b2Vec2;
class CustomBaseObject;
class CustomPhysics;
class DemoTopdownController : public Component
{
public:
    DemoTopdownController();
    ~DemoTopdownController();
    virtual void Initialize()       override;
    virtual void Update(float dt)   override;
    eDemoTopdownPlayerState GetControllerState() const;
private:
    void inputUpdate(float dt);
    void shoot(const b2Vec2& direction);
    void applyDamage(int damage);
public:
    float               mSpriteRotationOffset;
    float               mMaximumSpeed;
    float               mReshotCount;
    float               mBulletSpeed;
    float               mBulletLifeCount;
    int                 mMaxHealth;
    float               mDamagedCount;
    float               mDeathCount;
    float               mGameOverCount;
private:
    CustomPhysics*      mPhysics;
    eDemoTopdownPlayerState    mState;
    float               mStateTimer;
    float               mTimer;
    int                 mHealth;
    CustomBaseObject*   mGameOverScreen;
    CustomBaseObject**  mHealthObjects;
};
