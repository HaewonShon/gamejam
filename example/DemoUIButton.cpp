#include "DemoUIButton.h"
#include "engine/State.h"
#include "engine/Object.h"
#include "engine/Sprite.h"
#include "Command.h"
#include "CustomSprite.h"
#include "Intersect.h"

DemoUIButton::DemoUIButton() :
    Component(eComponentTypes::DemoUIButton),
    mButtonEvent(nullptr),
    mDefaultSprite(nullptr),
    mHoveredSprite(nullptr)
{
}

DemoUIButton::~DemoUIButton()
{
    // deallocate CustomSprite and Command
    delete mDefaultSprite;
    mDefaultSprite = nullptr;
    delete mHoveredSprite;
    mHoveredSprite = nullptr;
    delete mButtonEvent;
    mButtonEvent = nullptr;
}

void DemoUIButton::Initialize()
{
    // if there is default sprite, delete it.
    if (mDefaultSprite)
    {
        delete mDefaultSprite;
        mDefaultSprite = nullptr;
    }
    // Load default sprite image
    mDefaultSprite = new CustomSprite;
    mDefaultSprite->Initialize(State::sCurrentState->m_renderer, mDefaultSpriteFile);
    // Set default sprite to owner's sprite
    mOwner->sprite = std::move(*mDefaultSprite);


    // if there is hovered sprite, delete it.
    if (mHoveredSprite)
    {
        delete mHoveredSprite;
        mHoveredSprite = nullptr;
    }
    // Load hovered sprite image
    mHoveredSprite = new CustomSprite;
    mHoveredSprite->Initialize(State::sCurrentState->m_renderer, mHoveredSpriteFile);

}

void DemoUIButton::Update(float /*dt*/)
{
    // mouse is not on button
    const bool isColliding = Intersect::PointToBox(State::sCurrentState->m_input->GetMousePosInScreen(), 
                                        { mOwner->transform.position.x, mOwner->transform.position.y }, 
                                        mOwner->transform.GetScale());
    // mouse is not on button, set default sprite
    if(!isColliding)
    {
        mOwner->sprite = std::move(*mDefaultSprite);
    }
    // mouse is on button, set hovered sprite
    else 
    {
        mOwner->sprite = std::move(*mHoveredSprite);
        // if there is mouse event and Mouse Left button is clicked, excute commnad.
        if (mButtonEvent && State::sCurrentState->m_input->IsTriggered(SDL_BUTTON_LEFT))
        {
            mButtonEvent->Execute();
        }
    }

}