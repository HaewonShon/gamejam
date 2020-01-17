#include "DemoLv2Controller.h"
#include "engine/State.h"
#include "CustomBaseObject.h"
#include "CustomPhysics.h"

DemoLv2Controller::DemoLv2Controller():
    Component(eComponentTypes::DemoLv2Controller),
    mPhysics(nullptr)
{
}

DemoLv2Controller::~DemoLv2Controller()
{
}

void DemoLv2Controller::Initialize()
{
    mPhysics = &(dynamic_cast<CustomBaseObject*>(mOwner)->customPhysics);
}

void DemoLv2Controller::Update(float /*dt*/)
{
    // Make box jump, move left and right
    if (State::m_input->IsTriggered((SDL_SCANCODE_UP)))
        mPhysics->AddForce(0.f, 10.f);

    if (State::m_input->IsTriggered((SDL_SCANCODE_RIGHT)))
        mPhysics->AddForce(10.f, 0.f);

    if (State::m_input->IsTriggered((SDL_SCANCODE_LEFT)))
        mPhysics->AddForce(-10.f, 0.f);
}
