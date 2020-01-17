#include "DemoCameraLogic.h"
#include "engine/State.h"
#include "engine/Object.h"
#include "engine/Camera.h"
#include "DemoPlayerController.h"
#include "MathUtils.h"

DemoCameraLogic::DemoCameraLogic():
    Component(eComponentTypes::DemoCameraLogic),
    mState(eDemoCameraState::Normal),
    mCamera(nullptr),
    mTarget(nullptr),
    mTimer(0),
    mPositionOffset(0, 200)
{
}

DemoCameraLogic::~DemoCameraLogic()
{
    mCamera->rotation = 0;
    mCamera->position.z = 0;
}

void DemoCameraLogic::Initialize()
{
    // get camera
    mCamera = State::sCurrentState->m_pCamera;
    // get player object as a target
    mTarget = State::sCurrentState->GetObject("Player");
}

void DemoCameraLogic::Update(float dt)
{
    // if there is no target, return
    if (!mTarget)
        return;

    // based on current state, do different logic
    switch (mState)
    {
    case eDemoCameraState::Normal:
        break;
    case eDemoCameraState::Rotate:
        mTimer += dt;
        //  During 0 ~ 0.5 second, camera rotates from 0 degree to -10 degree
        if (mTimer <= 0.5f)
        {
            mCamera->rotation = MathUtils::Lerp(0, -10.f, mTimer * 2.f);
        }
        //  During 0.5 ~ 1.0 second, camera rotates from -10 degree to 0 degree
        else if (mTimer > 0.5f && mTimer < 1.f)
        {
            mCamera->rotation = MathUtils::Lerp(-10.f, 0, (mTimer * 2.f - 1.f));
        }
        // After 1 second, back to normal state
        else //if (mTimer >= 1.f)
        {
            mCamera->rotation = 0;
            mTimer = 0;
            mState = eDemoCameraState::Normal;
        }
        break;
    case eDemoCameraState::ZoomIn:
        // linearly interpolate camera's position z (zoom) from 0 to -200.f
        mTimer += dt;
        mCamera->position.z = MathUtils::Lerp(0, -200.f, mTimer);
        break;
    default:
        break;
    }
}

/**
 * \brief 
 * Set camera logic's state
 * 
 * \param state 
 * Camera logic state
 */
void DemoCameraLogic::SetCameraState(eDemoCameraState state)
{
    mTimer = 0;
    mState = state;
}

/**
 * \brief 
 * Syncronize Camera's position with Target's position.
 * It should be called after Update current State's physics to guarantee to follow exact target's position.
 */
void DemoCameraLogic::SyncCameraWithTarget()
{
    // chase target logic
    mCamera->position.x = mTarget->transform.position.x + mPositionOffset.x;
    mCamera->position.y = mTarget->transform.position.y + mPositionOffset.y;
}
