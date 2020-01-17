/******************************************************************************/
/*!
\file   DemoPlayerController.h
\author Hun Yang
\par    email: hun.yang8456@gmail.com
\par    GAM150 demo
\date   2019/04/28

Platformer demo's player controller.
It does not affect player's position, instead it control player's input, health, and state
*/
/******************************************************************************/
#pragma once
#include "DemoPlatformerController.h"
#include <Box2D/Common/b2Math.h>

enum class eDemoPlayetState
{
    Normal,
    Damaged,
    Dead,
    GameOver
};

class DemoCameraLogic;
class CustomBaseObject;
class DemoPlayerController : public DemoPlatformerController
{
public:
    DemoPlayerController();
    ~DemoPlayerController();
    virtual void Initialize() override;
    virtual void Update(float dt) override;

    void ApplyDamage(unsigned damage);
    void RestoreHealth(unsigned health);
    eDemoPlayetState GetPlayerState() const;
private:
    void    inputUpdate();
public:
    static b2Vec2       sStartPosition;
    float               mDamagedCount;
    float               mDeathCount;
    float               mGameOverCount;
    float               mMinimumBottom;
    int                 mMaxHealth;
private:
    eDemoPlayetState    mState;
    int                 mHealth;
    float               mTimer;
    CustomBaseObject*   mGameOverScreen;
    CustomBaseObject*   mCameraController;
    CustomBaseObject**  mHealthObjects;
    DemoCameraLogic*    mCameraLogic;
};
