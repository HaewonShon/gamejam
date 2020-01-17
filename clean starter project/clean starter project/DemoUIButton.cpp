#include "DemoUIButton.h"
#include "engine/State.h"
#include "engine/Object.h"
#include "engine/Sprite.h"
#include "Command.h"
#include "CustomSprite.h"
#include "Game.h"

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
    auto MousePos  = State::m_input->GetMousePos();
    MousePos.x = MousePos.x - State::m_game->m_width  * 0.5f;
    MousePos.y = State::m_game->m_height * 0.5f - MousePos.y;
    const bool isColliding = PointToBox(MousePos,
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

bool DemoUIButton::PointToBox(const b2Vec2& point, const b2Vec2& boxCenter, const b2Vec2& boxScale)
{
    // Get half scale
    b2Vec2 halfScale(boxScale.x * 0.5f, boxScale.y * 0.5f);


    // move point to box model space
    b2Vec2 subPosition(
        point.x - boxCenter.x,
        point.y - boxCenter.y);

    return (
        (subPosition.x <= halfScale.x) &&
        (subPosition.x >= -halfScale.x) &&
        (subPosition.y <= halfScale.y) &&
        (subPosition.y >= -halfScale.y));
}
