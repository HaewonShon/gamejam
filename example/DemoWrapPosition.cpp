#include "DemoWrapPosition.h"
#include "engine/Object.h"
#include "engine/Transform.h"
#include "engine/State.h"
#include "CustomBaseObject.h"
#include "MathUtils.h"

DemoWrapPosition::DemoWrapPosition():
    Component(eComponentTypes::DemoWrapPosition),
    mTransform(nullptr),
    mPositionOffest(5.f)
{
}

DemoWrapPosition::~DemoWrapPosition()
{
}

void DemoWrapPosition::Initialize()
{
    // get owner's transform pointer
    mTransform = &(mOwner->transform);
}

void DemoWrapPosition::Update(float /*dt*/)
{
    // get screen's half scale
    b2Vec2 screenHalfScale      (State::sCurrentState->m_width * 0.5f, State::sCurrentState->m_height * 0.5f);
    // object's bottom left position (added position offset)
    b2Vec2 BottomLeft           (mTransform->position.x - mTransform->GetHalfScale().x + mPositionOffest,
                                 mTransform->position.y - mTransform->GetHalfScale().y + mPositionOffest);
    // object's top right position (added position offset)
    b2Vec2 TopRight             (mTransform->position.x + mTransform->GetHalfScale().x - mPositionOffest,
                                 mTransform->position.y + mTransform->GetHalfScale().y - mPositionOffest);
    // new position
    b2Vec2 newPosition          (mTransform->position.x, mTransform->position.y);


    // if object go out into screen left, wrap position to screen right
    if (TopRight.x <= -screenHalfScale.x)
    {
        newPosition.x = screenHalfScale.x + mTransform->GetHalfScale().x - mPositionOffest;
    }
    // if object go out into screen right, wrap position to screen left
    else if (BottomLeft.x >= screenHalfScale.x)
    {
        newPosition.x = -(screenHalfScale.x + mTransform->GetHalfScale().x + mPositionOffest);
    }


    // if object go out into screen down, wrap position to screen up
    if (TopRight.y <= -screenHalfScale.y)
    {
        newPosition.y = screenHalfScale.y + mTransform->GetHalfScale().y - mPositionOffest;
    }
    // if object go out into screen up, wrap position to screen down
    else if (BottomLeft.y >= screenHalfScale.y)
    {
        newPosition.y = -(screenHalfScale.y + mTransform->GetHalfScale().y) + mPositionOffest;
    }

    // Position Apply
    dynamic_cast<CustomBaseObject*>(mOwner)->customPhysics.SetPosition(newPosition.x, newPosition.y);
}
