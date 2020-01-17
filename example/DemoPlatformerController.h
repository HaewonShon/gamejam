/******************************************************************************/
/*!
\file   DemoPlatformerController.h
\author Hun Yang
\par    email: hun.yang8456@gmail.com
\par    GAM150 demo
\date   2019/04/15

basic platformer controller
It updates custom physics's velocity based on Inputs
*/
/******************************************************************************/
#pragma once
#include "Component.h"

enum class eDemoControllerState
{
    Stand,
    Walk,
    Jump,
    Count
};

enum class eDemoKeyInput
{
    GoLeft,
    GoRight,
    GoDown,
    Jump,
    Count
};

class CustomPhysics;
class DemoPlatformerController : public Component
{
public:
    DemoPlatformerController();
    DemoPlatformerController(eComponentTypes type);
    ~DemoPlatformerController();
    virtual void Initialize() override;
    virtual void Update(float dt) override;
    eDemoControllerState GetControllerState(void) const;
private:
protected:
    bool*                   mInputs;
    float                   mWalkSpeed;
    float                   mJumpWalkSpeed;
    float                   mJumpSpeed;
    float                   mMinJumpSpeed;
    float                   mMaxFallingSpeed;
private:
    eDemoControllerState    mState;
    CustomPhysics*          mPhysics            = nullptr;
    bool                    mbIsGroundOn;
};
