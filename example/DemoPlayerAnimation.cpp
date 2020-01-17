#include "DemoPlayerAnimation.h"
#include "CustomSprite.h"
#include "engine/State.h"
#include "engine/Object.h"
#include "DemoPlatformerController.h"

DemoPlayerAnimation::DemoPlayerAnimation():
    Component(eComponentTypes::DemoPlayerAnimation),
    mPlayerStand(nullptr),
    mPlayerWalk(nullptr),
    mPlayerJump(nullptr)
{
}

DemoPlayerAnimation::~DemoPlayerAnimation()
{
    // deletea all allocated Customsprite
    delete mPlayerStand;
    mPlayerStand = nullptr;
    delete mPlayerWalk;
    mPlayerWalk = nullptr;
    delete mPlayerJump;
    mPlayerJump = nullptr;
}

void DemoPlayerAnimation::Initialize()
{
    // find controller component in same object
    mOwner->GetComponent(eComponentTypes::DemoPlayerController, mController);
    // allocate and load image
    createCustomSprite(mPlayerStand, mPlayerStandFile);
    createCustomSprite(mPlayerWalk, mPlayerWalkFile, true, 8, 12.f);
    createCustomSprite(mPlayerJump, mPlayerJumpFile);
    // set stand sprite first
    mOwner->sprite = std::move(*mPlayerStand);
}

void DemoPlayerAnimation::Update(float /*dt*/)
{
    // based on controller's state, change current sprite to proper one
    switch(mController->GetControllerState())
    {
    case eDemoControllerState::Stand:
        if (mOwner->sprite.GetTexture() != mPlayerStand->GetTexture())
        {
            mOwner->sprite = std::move(*mPlayerStand);
        }
        break;
    case eDemoControllerState::Walk:
        if (mOwner->sprite.GetTexture() != mPlayerWalk->GetTexture())
        {
            mOwner->sprite = std::move(*mPlayerWalk);
        }
        break;
    case eDemoControllerState::Jump:
        if (mOwner->sprite.GetTexture() != mPlayerJump->GetTexture())
        {
            mOwner->sprite = std::move(*mPlayerJump);
        }
        break;
    default:
        break;
    }
}

void DemoPlayerAnimation::createCustomSprite(CustomSprite*& sprite, std::string filePath, bool isAnimation, unsigned frames, float speed)
{
    // if sprite exist, delete it
    if (sprite)
    {
        delete sprite;
        sprite = nullptr;
    }
    // Load image
    sprite = new CustomSprite;
    sprite->Initialize(State::sCurrentState->m_renderer, filePath, isAnimation, frames, speed);
}
