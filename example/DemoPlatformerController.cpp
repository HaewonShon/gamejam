#include "DemoPlatformerController.h"
#include "engine/State.h"
#include "engine/Object.h"
#include "CustomBaseObject.h"
#include "ContactData.h"

DemoPlatformerController::DemoPlatformerController():
    Component(eComponentTypes::DemoPlatformerController),
    mState(eDemoControllerState::Stand),
    mInputs(nullptr),
    mWalkSpeed(10.f),
    mJumpWalkSpeed(5.0f),
    mJumpSpeed(13.f),
    mMinJumpSpeed(5.f),
    mMaxFallingSpeed(-30)
{

}

DemoPlatformerController::DemoPlatformerController(eComponentTypes type):
    Component(type),
    mState(eDemoControllerState::Stand),
    mInputs(nullptr),
    mWalkSpeed(10.f),
    mJumpWalkSpeed(6.0f),
    mJumpSpeed(13.f),
    mMinJumpSpeed(5.f),
    mMaxFallingSpeed(-30)
{
}

DemoPlatformerController::~DemoPlatformerController()
{
    mOwner->sprite.flip = SDL_FLIP_NONE;
    delete mInputs;
    mInputs = nullptr;
    mPhysics = nullptr;
}

void DemoPlatformerController::Initialize()
{
    // if there is something in mInputs, delete them
    if(mInputs)
    {
        delete mInputs;
        mInputs = nullptr;
    }

    // allocate inputs
    mInputs = new bool [static_cast<int>(eDemoKeyInput::Count)];
    for (int i = 0; i < static_cast<int>(eDemoKeyInput::Count); ++i)
    {
        mInputs[i] = false;
    }

    // Store custom physics
    mPhysics = &(dynamic_cast<CustomBaseObject*>(mOwner)->customPhysics);
}

void DemoPlatformerController::Update(float /*dt*/)
{
    b2Vec2 newVelocity = mPhysics->GetVelocity();

    // if there is no foot sensor, just set on ground
    if (mPhysics->mSensorContactData.size() <= 0)
    {
        mbIsGroundOn = true;
    }
    else
    {
        // if foot sensor contact with something, set on ground.
        mbIsGroundOn = (mPhysics->mSensorContactData[0]->NumContacts > 0);
    }


    // Update player velocity based on current state
    switch(mState)
    {
    case eDemoControllerState::Stand:
        {
            // set velocity zero
            newVelocity.SetZero();
            // floating in the air
            if(!mbIsGroundOn)
            {
                mState = eDemoControllerState::Jump;
            }

            // walk
            if (mInputs[static_cast<int>(eDemoKeyInput::GoLeft)] 
                != mInputs[static_cast<int>(eDemoKeyInput::GoRight)])
            {
                mState = eDemoControllerState::Walk;
            }
            // jump
            else if (mInputs[static_cast<int>(eDemoKeyInput::Jump)])
            {
                newVelocity.y = mJumpSpeed;
                mState = eDemoControllerState::Jump;
            }
        }
        break;
    case eDemoControllerState::Walk:
        {
            // walk
            if (mInputs[static_cast<int>(eDemoKeyInput::GoRight)])
            {
                newVelocity.x = mWalkSpeed;
                // animation flip off
                mOwner->sprite.flip = SDL_FLIP_NONE;
            }
            else if (mInputs[static_cast<int>(eDemoKeyInput::GoLeft)])
            {
                newVelocity.x = -mWalkSpeed;
                // animation flip on
                mOwner->sprite.flip = SDL_FLIP_HORIZONTAL;
            }
            else
            {
                mState = eDemoControllerState::Stand;
                newVelocity.SetZero();
            }

            // jump
            if (mInputs[static_cast<int>(eDemoKeyInput::Jump)])
            {
                newVelocity.y = mJumpSpeed;
                mState = eDemoControllerState::Jump;
            }
        }
        break;
    case eDemoControllerState::Jump:
        {
        //printf("[Velocity: %.2f, %.2f]\n", newVelocity.x, newVelocity.y);
            newVelocity.y = std::max(newVelocity.y, mMaxFallingSpeed);
            if(!mInputs[static_cast<int>(eDemoKeyInput::Jump)]
                && newVelocity.y > 0)
            {
                //printf("[2] Velocity Y: %.2f\n", newVelocity.y);
                newVelocity.y = std::min(newVelocity.y, mMinJumpSpeed);
            }

            // walk
            if (mInputs[static_cast<int>(eDemoKeyInput::GoRight)])
            {
                newVelocity.x = mJumpWalkSpeed;
                // animation flip off
                mOwner->sprite.flip = SDL_FLIP_NONE;
            }
            else if (mInputs[static_cast<int>(eDemoKeyInput::GoLeft)])
            {
                newVelocity.x = -mJumpWalkSpeed;
                // animation flip on
                mOwner->sprite.flip = SDL_FLIP_HORIZONTAL;
            }
            else
            {
                newVelocity.x = 0;
            }

            // stand
            if (mbIsGroundOn)
            {
                mState = eDemoControllerState::Stand;
            }
        }
        break;
    default:
        break;
    }

    // Apply new velocity
    mPhysics->SetVelocity(newVelocity);
}

eDemoControllerState DemoPlatformerController::GetControllerState() const
{
    return mState;
}
