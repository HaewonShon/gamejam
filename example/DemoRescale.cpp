#include "DemoRescale.h"
#include "engine/Object.h"
#include "engine/State.h"

DemoRescale::DemoRescale():
    Component(eComponentTypes::DemoRescale)
{
}

DemoRescale::~DemoRescale()
{
}

void DemoRescale::Initialize()
{
    // store initial scale
    mInitialScale = mOwner->transform.GetScale();
}

void DemoRescale::Update(float /*dt*/)
{
    // based on current screen width and height, change object's scale
    mOwner->transform.SetScale(mInitialScale.x * State::m_width, mInitialScale.y * State::m_height);
}
