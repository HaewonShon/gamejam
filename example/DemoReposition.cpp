#include "DemoReposition.h"
#include "engine/State.h"
#include "engine/Object.h"

DemoReposition::DemoReposition():
    Component(eComponentTypes::DemoReposition),
    mBase(DemoRepositionBase::TopLeft)
{
}

DemoReposition::~DemoReposition()
{

}

void DemoReposition::Initialize()
{
    // store initial position
    mPositionByBase.Set(mOwner->transform.position.x, mOwner->transform.position.y);
}

void DemoReposition::Update(float /*dt*/)
{
    b2Vec2 basePosition;

    // based on current screen width / height and base point, get base position
    switch (mBase)
    {
    case DemoRepositionBase::TopLeft:
        basePosition.Set(-State::sCurrentState->m_width * 0.5f, State::sCurrentState->m_height * 0.5f);
        break;
    case DemoRepositionBase::TopRight:
        basePosition.Set(State::sCurrentState->m_width * 0.5f, State::sCurrentState->m_height * 0.5f);
        break;
    case DemoRepositionBase::BottomLeft:
        basePosition.Set(-State::sCurrentState->m_width * 0.5f, -State::sCurrentState->m_height * 0.5f);
        break;
    case DemoRepositionBase::BottomRight:
        basePosition.Set(State::sCurrentState->m_width * 0.5f, -State::sCurrentState->m_height * 0.5f);
        break;
    default:
        return;
    }

    // update object's position 
    mOwner->transform.position.x = basePosition.x + mPositionByBase.x;
    mOwner->transform.position.y = basePosition.y + mPositionByBase.y;
}

void DemoReposition::SetBase(DemoRepositionBase base)
{
    // set base point type
    mBase = base;
}
