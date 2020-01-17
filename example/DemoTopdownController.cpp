#include "DemoTopdownController.h"
#include "engine/State.h"
#include "CustomBaseObject.h"
#include "MathUtils.h"
#include "Bullet.h"
#include "Color.h"
#include "PlatformerContactListener.h"
#include "CustomBaseObject.h"
#include "engine/State.h"
#include "Game.h"
#include "DemoReposition.h"
#include "ContactData.h"
#include "CustomPhysics.h"

DemoTopdownController::DemoTopdownController():
    Component(eComponentTypes::DemoTopdownController),
    mState(eDemoTopdownPlayerState::Normal),
    mSpriteRotationOffset(90.f),
    mMaximumSpeed(30.f),
    mReshotCount(0.5f),
    mBulletSpeed(50.f),
    mBulletLifeCount(0.7f),
    mTimer(0),
    mStateTimer(0),
    mMaxHealth(5),
    mHealth(0),
    mDamagedCount(2.5f),
    mDeathCount(1.5f),
    mGameOverCount(2.f)
{
}

DemoTopdownController::~DemoTopdownController()
{
    mOwner->sprite.color.a = 255;
    delete[]mHealthObjects;
}

void DemoTopdownController::Initialize()
{
    // set pointer to custom physics component
    mPhysics = &(dynamic_cast<CustomBaseObject*>(mOwner)->customPhysics);


    mGameOverScreen = dynamic_cast<CustomBaseObject*>(State::sCurrentState->GetObject("GameOverScreen"));

    // health objects (HUD) initialize
    mHealth = mMaxHealth;
    mHealthObjects = new CustomBaseObject*[mMaxHealth];

    b2Vec2 healthScale(64.f, 64.f);
    for (int i = 0; i < mMaxHealth; ++i)
    {
        // allocate object 
        mHealthObjects[i] = new CustomBaseObject;
        // name
        std::string name = "PlayerHealth" + std::to_string(i + 1);
        mHealthObjects[i]->SetName(name.c_str());

        // set position and scale
        mHealthObjects[i]->transform.position.Set(
            healthScale.x * (i + 1),
            - healthScale.y * 1.5f, 0);
        mHealthObjects[i]->transform.SetScale(healthScale.x, healthScale.y);

        // sprite set
        mHealthObjects[i]->sprite.LoadImage("texture/Lives.png", State::sCurrentState->m_renderer);
        mHealthObjects[i]->sprite.isHud = true;

        DemoReposition* reposition = dynamic_cast<DemoReposition*>(
            State::sCurrentState->AddComponentToObject(
                mHealthObjects[i], 
                eComponentTypes::DemoReposition));
        reposition->SetBase(DemoRepositionBase::TopLeft);
        //reposition->mPositionByBase.Set(healthScale.x * (i + 1), -healthScale.y * 1.5f);

        State::sCurrentState->AddDynamicObject(mHealthObjects[i]);
    }

    // set Player's contact user data
    ContactData* data = new ContactData;
    data->Type = eContactTypes::Player;
    data->NumContacts = 0;
    data->Owner = dynamic_cast<CustomBaseObject*>(mOwner);
    dynamic_cast<CustomBaseObject*>(mOwner)->customPhysics.SetContactUserData(data);
}

void DemoTopdownController::Update(float dt)
{
    CustomBaseObject* owner = dynamic_cast<CustomBaseObject*>(mOwner);


    switch(mState)
    {
    case eDemoTopdownPlayerState::Normal:
        inputUpdate(dt);
        if (owner->customPhysics.mContactData->NumContacts > 0)
        {
            applyDamage(1);
        }
        break;
    case eDemoTopdownPlayerState::Damaged:
        inputUpdate(dt);
        mStateTimer += dt;
        if (mStateTimer >= mDamagedCount)
        {
            mState = eDemoTopdownPlayerState::Normal;
            mStateTimer = 0.f;
            mOwner->sprite.color.a = 255;
            owner->customPhysics.mContactData->NumContacts = 0;
        }
        break;
    case eDemoTopdownPlayerState::Dead:
        mTimer += dt;
        // interpolate player transparency
        mOwner->sprite.color.a = static_cast<unsigned char>(b2Clamp(MathUtils::Lerp(255.f, 0.f, mTimer), 0.f, 255.f));
        if (mTimer > mDeathCount)
        {
            mState = eDemoTopdownPlayerState::GameOver;
            mTimer = 0;
            if (mGameOverScreen)
                mGameOverScreen->sprite.isVisible = true;
        }
        break;
    case eDemoTopdownPlayerState::GameOver:
        mTimer += dt;
        if (mTimer > mGameOverCount)
        {
            State::sCurrentState->m_game->Change(LV_MainMenu);
        }
        break;
    default:
        break;
    }

}

void DemoTopdownController::inputUpdate(float dt)
{
    CustomBaseObject* owner = dynamic_cast<CustomBaseObject*>(mOwner);
    b2Vec2 velocity(owner->customPhysics.GetVelocity());


    b2Vec2 mouse(State::sCurrentState->m_input->GetMousePosInScreen());
    b2Vec2 player(owner->transform.position.x, owner->transform.position.y);
    b2Vec2 direction = mouse - player;
    direction.Normalize();

    float newRotation = atan2(direction.y, direction.x);
    owner->transform.rotation = MathUtils::RadianToDegree(newRotation) - mSpriteRotationOffset;

    if (State::sCurrentState->m_input->IsPressed(SDL_SCANCODE_W))
    {
        b2Vec2 newForce = direction;

        // Speed Chnage gradually
        if (direction.x > 0)
        {
            newForce.x = b2Min(velocity.x + 0.1f, mMaximumSpeed) - velocity.x;
        }
        else
        {
            newForce.x = -(b2Max(velocity.x - 0.1f, -mMaximumSpeed) - velocity.x);
        }

        if (direction.y > 0)
        {
            newForce.y = b2Min(velocity.y + 0.1f, mMaximumSpeed) - velocity.y;
        }
        else
        {
            newForce.y = -(b2Max(velocity.y - 0.1f, -mMaximumSpeed) - velocity.y);
        }
        newForce.x *= direction.x * mMaximumSpeed;
        newForce.y *= direction.y * mMaximumSpeed;

        owner->customPhysics.AddForce(newForce.x, newForce.y);
        owner->emitter.SetActive(true);
        owner->emitter.SetDegree(owner->transform.rotation);
    }
    else
    {
        owner->emitter.SetActive(false);
    }


    // Shoot bullet
    mTimer += dt;
    if (State::sCurrentState->m_input->IsPressed(SDL_BUTTON_LEFT))
    {
        // if timer is over reshot count (second), shoot bullet again
        if (mTimer >= mReshotCount)
        {
            mTimer = 0;
            shoot(direction);
        }
    }

    owner->customPhysics.GetBody()->SetLinearDamping(1.0f);
}

void DemoTopdownController::shoot(const b2Vec2& direction)
{
    CustomBullet *newBullet = new CustomBullet;

    newBullet->SetName("Bullet");
    newBullet->transform.position.Set(
        mOwner->transform.position.x + direction.x * (mOwner->transform.GetHalfScale().x + 10.f),
        mOwner->transform.position.y + direction.y * (mOwner->transform.GetHalfScale().y + 10.f), 0.f);
    newBullet->transform.SetScale(12.f, 48.f);
    newBullet->transform.rotation = mOwner->transform.rotation;

    newBullet->sprite.color = Color::WHITE;
    newBullet->sprite.LoadImage("texture/Bullet.png", State::m_renderer);

    newBullet->customPhysics.GenerateBody(State::sCurrentState->GetCustomPhysicsWorld(), &newBullet->transform);
    ContactData* userData = new ContactData;
    userData->Type = eContactTypes::Bullet;
    userData->NumContacts = 0;
    userData->Owner = newBullet;
    newBullet->customPhysics.SetContactUserData(userData);

    newBullet->mLifeCount = 0.7f;
    State::sCurrentState->AddComponentToObject(newBullet, eComponentTypes::DemoWrapPosition);
    State::sCurrentState->AddDynamicObjectAndInitialize(newBullet);
    State::sCurrentState->AddCustomPhysicsComponent(newBullet);

    // Have bullet move in the direction the turret is facing
    newBullet->customPhysics.SetVelocity(direction.x * mBulletSpeed, direction.y * mBulletSpeed);
    newBullet->customPhysics.ActiveGhostCollision(false);
}

void DemoTopdownController::applyDamage(int damage)
{

    if (mState == eDemoTopdownPlayerState::Normal)
    {
        // make health objects transparent
        for (int i = mHealth - 1; i >= 0 && i >= (mHealth - static_cast<int>(damage)); --i)
        {
            mHealthObjects[i]->sprite.color.a = 0;
        }

        // apply damage
        mHealth -= damage;

        // change into damaged state
        if (mHealth > 0)
        {
            mState = eDemoTopdownPlayerState::Damaged;
            mTimer = 0;
            mOwner->sprite.color.a /= 2;
        }
        // change into player death
        else
        {
            mState = eDemoTopdownPlayerState::Dead;
            mTimer = 0;
            CustomBaseObject* owner = dynamic_cast<CustomBaseObject*>(mOwner);
            owner->customPhysics.bodyType = CustomPhysics::STATIC;
            owner->customPhysics.GetBody()->SetType(b2BodyType::b2_staticBody);
        }
    }
}

eDemoTopdownPlayerState DemoTopdownController::GetControllerState() const
{
    return mState;
}
