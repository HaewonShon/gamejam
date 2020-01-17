#include "DemoChasePlayer.h"
#include "CustomBaseObject.h"
#include "engine/State.h"
#include "Intersect.h"
#include "DemoEnemySpawner.h"
#include "MathUtils.h"
#include "DemoTopdownController.h"
#include "DemoPlayerController.h"
#include "ContactData.h"

DemoChasePlayer::DemoChasePlayer():
    Component(eComponentTypes::DemoChasePlayer),
    mPhysics(nullptr),
    mState(eDemoChaseEnemyState::Normal),
    mSpeed(10.f),
    mDetectRadius(400.f),
    mTimer(0),
    mDeathCount(1.f),
    mTopdownController(nullptr),
    mPlatformerController(nullptr)
{
}

DemoChasePlayer::~DemoChasePlayer()
{
}

void DemoChasePlayer::Initialize()
{
    // set pointer to the custom physics comopnent 
    mPhysics = &(dynamic_cast<CustomBaseObject*>(mOwner)->customPhysics);
    // Find 'Player' object
    mPlayer = dynamic_cast<CustomBaseObject*>(State::sCurrentState->GetObject("Player"));
    // get proper controller component
    mPlayer->GetComponent(eComponentTypes::DemoTopdownController, mTopdownController);
    if (!mTopdownController)
    {
        mPlayer->GetComponent(eComponentTypes::DemoPlayerController, mPlatformerController);
    }
    b2Vec2 playerHalfScale = mPlayer->transform.GetHalfScale();


    // Set contact data
    ContactData* userData = new ContactData;
    userData->Type = eContactTypes::Enemy;
    userData->NumContacts = 0;
    userData->Owner = dynamic_cast<CustomBaseObject*>(mOwner);
    mPhysics->SetContactUserData(userData);
    
}

void DemoChasePlayer::Update(float dt)
{
    // if collide with bullet, set dead state and other conditions
    if (dynamic_cast<CustomBaseObject*>(mOwner)->customPhysics.mContactData->NumContacts > 0)
    {
        // set dead state
        mState = eDemoChaseEnemyState::Dead;
        // off physics 
        dynamic_cast<CustomBaseObject*>(mOwner)->customPhysics.ActivePhysics(false);
        // set sprite invisible
        mOwner->sprite.isVisible = false;
        // set particle effect on
        mOwner->emitter.SetActive(true);
    }

    switch (mState)
    {
    case eDemoChaseEnemyState::Normal:
        detectPlayer(true);
        break;
    case eDemoChaseEnemyState::Chase:
        chaseUpdate();
        break;
    case eDemoChaseEnemyState::Back:
        if (detectPlayer(false))
        {
            mTimer = 0;
            break;
        }
        backUpdate(dt);
        break;
    case eDemoChaseEnemyState::Dead:
        mTimer += dt;
        // after death, wait death count seconds for particle effect
        if (mTimer >= mDeathCount)
        {
            mTimer = 0;
            mOwner->isDead = true;
        }
        break;
    default:
        break;
    }
}

/**
 * \brief 
 * \param saveData 
 * Toggle to save return position velocity and position.
 * 
 * \return 
 */
bool DemoChasePlayer::detectPlayer(bool saveData)
{
    // if controller does not exist and player state is not normal, ignore detect player logic
    if (mTopdownController      && mTopdownController->GetControllerState() != eDemoTopdownPlayerState::Normal)
        return false;
    if (mPlatformerController   && mPlatformerController->GetPlayerState() != eDemoPlayetState::Normal)
        return false;

    // Check if player is on enemy's detect are or not.
    // * reason why circle shape is used for player is that 
    //   circle to circle collision check is cheaper than circle to box collision.
    if (Intersect::CircleToCircle(
            { mOwner->transform.position.x, mOwner->transform.position.y },     mDetectRadius,
            { mPlayer->transform.position.x, mPlayer->transform.position.y },   mPlayer->customPhysics.radius))
    {
        if (saveData)
        {
            // Remember position & velocity to return 
            mReturnPositoin.Set(mOwner->transform.position.x, mOwner->transform.position.y);
            mInitialVelocity = mPhysics->GetVelocity();
        }

        mState = eDemoChaseEnemyState::Chase;
        return true;
    }
    return false;
}

void DemoChasePlayer::chaseUpdate()
{
    // get direction vector from player to enemy object
    b2Vec2 direction =  b2Vec2(mPlayer->transform.position.x, mPlayer->transform.position.y) -
                        b2Vec2(mOwner->transform.position.x, mOwner->transform.position.y);
    // normalize direction vector for constant speed
    direction.Normalize();
    // multiply velocity with direction
    mPhysics->SetVelocity(direction.x * mSpeed, direction.y * mSpeed);
    // if enemy's actual body collide with player, set back state
    if (mPhysics->IsCollidingWith(mPlayer))
    {
        mReturnStartPosition.Set(mOwner->transform.position.x, mOwner->transform.position.y);
        mState = eDemoChaseEnemyState::Back;
    }
}

void DemoChasePlayer::backUpdate(float dt)
{
    mTimer += dt;

    // linearly interpolate enemy's position from return start position to return position for 1 second
    mPhysics->SetPosition(
        MathUtils::Lerp(mReturnStartPosition.x, mReturnPositoin.x, mTimer),
        MathUtils::Lerp(mReturnStartPosition.y, mReturnPositoin.y, mTimer));


    // after 1 second, enemy come back to return position, so reset position, velocity and state for Normal.
    if (mTimer >= 1.f)
    {
        mTimer = 0;
        mState = eDemoChaseEnemyState::Normal;
        mPhysics->SetPosition(mReturnPositoin.x, mReturnPositoin.y);
        mPhysics->SetVelocity(mInitialVelocity.x, mInitialVelocity.y);
    }
}
