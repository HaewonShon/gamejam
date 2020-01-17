#include "DemoCollisionTrigger.h"
#include "engine/State.h"
#include "CustomBaseObject.h"
#include "Command.h"
#include "CheckPointCommand.h"
#include "DamageCommand.h"
#include "ChangeStateCommand.h"

DemoCollisionTrigger::DemoCollisionTrigger():
    Component(eComponentTypes::DemoCollisionTrigger),
    mTriggerType(eTriggerTypes::Always),
    mTarget(nullptr),
    mCommand(nullptr),
    mCommandType(eCommandTypes::INVALID),
    mReactiveCount(1),
    mTimer(0),
    mbIsTriggered(false),
    mDamage(1),
    mChangeLevel(LV_Level1)
{
}

DemoCollisionTrigger::~DemoCollisionTrigger()
{
    delete mCommand;
    mCommand = nullptr;
}

void DemoCollisionTrigger::Initialize()
{
    // set pointer to the object's custom physics
    mPhysics = &(dynamic_cast<CustomBaseObject*>(mOwner)->customPhysics);

    // if there is target name, find target object and set pointer to it.
    if (mTargetName.size() > 0)
    {
        mTarget = dynamic_cast<CustomBaseObject*>(State::sCurrentState->GetObject(mTargetName.c_str()));
    }


    // if there is no command type, ignore it.
    if (mCommandType != eCommandTypes::INVALID)
    {
        // Create command
        mCommand = State::sCurrentState->CreateCommand(mCommandType);

        // Based on each command type, initialize variables differently
        switch (mCommandType)
        {
        case eCommandTypes::CheckPointCommand:
            {
                CheckPointCommand* command = dynamic_cast<CheckPointCommand*>(mCommand);
                command->mTransform = &(mOwner->transform);
                command->mTarget = mTarget;
            }
            break;
        case eCommandTypes::DamageCommand:
            {
                DamageCommand * command = dynamic_cast<DamageCommand*>(mCommand);
                command->mDamage = mDamage;
                command->mTarget = mTarget;
            }
            break;
        case eCommandTypes::ChangeStateCommand:
            {
                ChangeStateCommand * command = dynamic_cast<ChangeStateCommand*>(mCommand);
                command->mChangeLevel = mChangeLevel;
            }
            break;
        default:
            break;
        }
    }
    
}

void DemoCollisionTrigger::Update(float dt)
{
    // if there is no target and command, escape.
    if (!mTarget || !mCommand)
        return;

    switch (mTriggerType)
    {
    case eTriggerTypes::Always:
        checkExecuteCommand();
        break;
    case eTriggerTypes::Once:
        if (!mbIsTriggered)
        {
            mbIsTriggered = checkExecuteCommand();
        }
        // if triggered on,
        else
        {
            // wait for ReactiveCount (second) to check colllision again
            mTimer += dt;
            if (mTimer >= mReactiveCount)
            {
                mTimer = 0.f;
                mbIsTriggered = false;
            }
        }
        break;
    case eTriggerTypes::Disappear:
        if (!mbIsTriggered)
        {
            mbIsTriggered = checkExecuteCommand();
        }
        // if triggered on,
        else
        {
            // Detroy object from object list
            mOwner->isDead = true;
        }
        break;
    default:
        break;
    }
    
}

void DemoCollisionTrigger::SetTiriggerType(eTriggerTypes type)
{
    mTriggerType = type;
}

eTriggerTypes DemoCollisionTrigger::GetTriggerType() const
{
    return mTriggerType;
}

bool DemoCollisionTrigger::checkExecuteCommand()
{
    // if target is colliding with this trap, excute command.
    if (dynamic_cast<CustomBaseObject*>(mOwner)->customPhysics.IsCollidingWith(mTarget))
    {
        mCommand->Execute();
        return true;
    }
    return false;
}
