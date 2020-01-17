#include "DemoEnemyController.h"
#include "CustomBaseObject.h"

DemoEnemyController::DemoEnemyController():
    DemoPlatformerController(eComponentTypes::DemoEnemyController),
    mMovingDistance(400.f)
{
    mWalkSpeed = 7.0f;
}

DemoEnemyController::~DemoEnemyController()
{
    mOwner->sprite.flip = SDL_FLIP_NONE;
}

void DemoEnemyController::Initialize()
{
    // Initialize 'DemoPlatformerController' component
    DemoPlatformerController::Initialize();
    // First set go to left
    mInputs[static_cast<int>(eDemoKeyInput::GoLeft)] = true;
    mMinPositionX = mOwner->transform.position.x - mMovingDistance * 0.5f;
    mMaxPositionX = mOwner->transform.position.x + mMovingDistance * 0.5f;
}


void DemoEnemyController::Update(float dt)
{
    // if enemy go left beyound minimun x position, set go to right
    if (mOwner->transform.position.x <= mMinPositionX)
    {
        mInputs[static_cast<int>(eDemoKeyInput::GoLeft)] = false;
        mInputs[static_cast<int>(eDemoKeyInput::GoRight)] = true;
    }
    // if enemy go right beyound maximun x position, set go to left
    else if (mOwner->transform.position.x >= mMaxPositionX)
    {
        mInputs[static_cast<int>(eDemoKeyInput::GoLeft)] = true;
        mInputs[static_cast<int>(eDemoKeyInput::GoRight)] = false;
    }

    // update velocity based on input
    DemoPlatformerController::Update(dt);
    // sprite update
    animationUpdate();
}

void DemoEnemyController::animationUpdate()
{
    // if enemy go left, not flip sprite
    if (mInputs[static_cast<int>(eDemoKeyInput::GoLeft)])
    {
        mOwner->sprite.flip = SDL_FLIP_NONE;
    }
    // if go right, flip sprite
    else
    {
        mOwner->sprite.flip = SDL_FLIP_HORIZONTAL;
    }
}
