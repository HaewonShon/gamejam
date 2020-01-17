/******************************************************************************/
/*!
\file   DemoCollisionTrigger.h
\author Hun Yang
\par    email: hun.yang8456@gmail.com
\par    GAM150 demo
\date   2019/04/28

It is component to chase player's position
*/
/******************************************************************************/
#pragma once
#include "Component.h"
#include "Game.h"

// enum class for 'DemoCollisionTrigger' component state
enum class eTriggerTypes
{
    Always,
    Once,
    Disappear

};

class CustomBaseObject;
class Command;
class DemoCollisionTrigger : public Component
{
public:
    DemoCollisionTrigger();
    ~DemoCollisionTrigger();
    virtual void Initialize()       override;
    virtual void Update(float dt)   override;

    void                SetTiriggerType     (eTriggerTypes type);
    eTriggerTypes       GetTriggerType      () const;
private:
    bool                checkExecuteCommand ();
public:
    std::string         mTargetName;
    eCommandTypes       mCommandType;
    float               mReactiveCount;
    int                 mDamage;
    Level_ID            mChangeLevel;
private:
    CustomPhysics*      mPhysics;
    eTriggerTypes       mTriggerType;
    CustomBaseObject*   mTarget;            // pointer to the target object
    Command*		    mCommand;           // pointer to the command to be excuted
    float               mTimer;             // Timer
    bool                mbIsTriggered;      // toggle to check if trigger is on
};
