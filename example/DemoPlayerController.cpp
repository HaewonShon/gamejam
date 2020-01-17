#include "DemoPlayerController.h"
#include "engine/State.h"
#include "Game.h"
#include "MathUtils.h"
#include "DemoReposition.h"
#include "PlatformerContactListener.h"
#include "DemoCameraLogic.h"
#include "ContactData.h"

b2Vec2 DemoPlayerController::sStartPosition;

DemoPlayerController::DemoPlayerController():
    DemoPlatformerController(eComponentTypes::DemoPlayerController),
    mState(eDemoPlayetState::Normal),
    mDamagedCount(1.f),
    mDeathCount(1.5f),
    mGameOverCount(2.f),
    mMinimumBottom(-2000.f),
    mMaxHealth(5),
    mTimer(0),
    mHealth(5),
    mGameOverScreen(nullptr),
    mHealthObjects(nullptr)
{
}

DemoPlayerController::~DemoPlayerController()
{
    mOwner->sprite.flip = SDL_FLIP_NONE;
    delete []mHealthObjects;
}

void DemoPlayerController::Initialize()
{
    DemoPlatformerController::Initialize();
    mGameOverScreen = dynamic_cast<CustomBaseObject*>(State::sCurrentState->GetObject("GameOverScreen"));
    CustomBaseObject* camera = dynamic_cast<CustomBaseObject*>(State::sCurrentState->GetObject("CameraController"));
    camera->GetComponent(eComponentTypes::DemoCameraLogic, mCameraLogic);
    // health objects (HUD) initialize
    mHealth = mMaxHealth;
    mHealthObjects = new CustomBaseObject*[mMaxHealth];
    b2Vec2 healthScale(64.f, 64.f);
    for (int i = 0; i < mMaxHealth; ++i)
    {
        // allocate object 
        mHealthObjects[i] = new CustomBaseObject;
        // name
        std::string name = "PlayerHealth" + std::to_string(i+1);
        mHealthObjects[i]->SetName(name.c_str());

        // set position and scale
        mHealthObjects[i]->transform.position.Set(
            healthScale.x * (i + 1), 
            - healthScale.y * 0.5f, 0);
        mHealthObjects[i]->transform.SetScale(healthScale.x, healthScale.y);

        // sprite set
        mHealthObjects[i]->sprite.LoadImage("texture/Lives.png", State::sCurrentState->m_renderer);
        mHealthObjects[i]->sprite.isHud = true;

        DemoReposition* reposition = dynamic_cast<DemoReposition*>(
            State::sCurrentState->AddComponentToObject(
                mHealthObjects[i],
                eComponentTypes::DemoReposition));
        reposition->SetBase(DemoRepositionBase::TopLeft);
        State::sCurrentState->AddDynamicObject(mHealthObjects[i]);
    }

    CustomBaseObject* owner = dynamic_cast<CustomBaseObject*>(mOwner);

    // Set contact data
    ContactData* userData = new ContactData;
    userData->Type = eContactTypes::Player;
    userData->NumContacts = 0;
    userData->Owner = owner;
    owner->customPhysics.SetContactUserData(userData);

}

void DemoPlayerController::Update(float dt)
{
    // prevent player form falling infinitely
    if (mOwner->transform.position.y < mMinimumBottom)
    {
        ApplyDamage(100);
    }

    switch(mState)
    {
    case eDemoPlayetState::Normal:
        inputUpdate();
        DemoPlatformerController::Update(dt);
        break;
    case eDemoPlayetState::Damaged:
        inputUpdate();
        DemoPlatformerController::Update(dt);
        mTimer += dt;
        if (mTimer >= mDamagedCount)
        {
            mState = eDemoPlayetState::Normal;
            mTimer = 0.f;
            mOwner->sprite.color.a = 255;
        }
        break;
    case eDemoPlayetState::Dead:
        mTimer += dt;
        // interpolate player transparency
        mOwner->sprite.color.a = static_cast<unsigned char>(b2Clamp(MathUtils::Lerp(255.f, 0.f, mTimer), 0.f, 255.f));
        if(mTimer > mDeathCount)
        {
            mOwner->sprite.color.a = 255;
            mState = eDemoPlayetState::GameOver;
            mTimer = 0;
            if (mGameOverScreen)
                mGameOverScreen->sprite.isVisible = true;
        }
        break;
    case eDemoPlayetState::GameOver:
        mTimer += dt;
        if (mTimer > mGameOverCount)
        {
            State::sCurrentState->m_game->Restart();
        }
        break;
    }
}

void DemoPlayerController::ApplyDamage(unsigned damage)
{
    if (mState == eDemoPlayetState::Normal)
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
            mState = eDemoPlayetState::Damaged;
            mTimer = 0;
            mOwner->sprite.color.a /= 2;
            mCameraLogic->SetCameraState(eDemoCameraState::Rotate);
        }
        // change into player death
        else
        {
            mState = eDemoPlayetState::Dead;
            mTimer = 0;
            CustomBaseObject* owner = dynamic_cast<CustomBaseObject*>(mOwner);
            owner->customPhysics.bodyType = CustomPhysics::STATIC;
            owner->customPhysics.GetBody()->SetType(b2BodyType::b2_staticBody);
            mCameraLogic->SetCameraState(eDemoCameraState::ZoomIn);
        }
    }
}

void DemoPlayerController::RestoreHealth(unsigned health)
{
    // make health objects visible
    for (const int recover = mHealth + health; mHealth < recover && mHealth < mMaxHealth; ++mHealth)
    {
        mHealthObjects[mHealth]->sprite.color.a = 255;
    }
}

eDemoPlayetState DemoPlayerController::GetPlayerState() const
{
    return mState;
}

void DemoPlayerController::inputUpdate()
{
    // Update Input key
    mInputs[static_cast<int>(eDemoKeyInput::GoLeft)] = State::sCurrentState->m_input->IsPressed(SDL_SCANCODE_LEFT);
    mInputs[static_cast<int>(eDemoKeyInput::GoRight)] = State::sCurrentState->m_input->IsPressed(SDL_SCANCODE_RIGHT);
    mInputs[static_cast<int>(eDemoKeyInput::GoDown)] = State::sCurrentState->m_input->IsPressed(SDL_SCANCODE_DOWN);
    mInputs[static_cast<int>(eDemoKeyInput::Jump)] = 
        State::sCurrentState->m_input->IsPressed(SDL_SCANCODE_SPACE) ||
        State::sCurrentState->m_input->IsPressed(SDL_SCANCODE_UP);
}
