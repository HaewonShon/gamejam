/******************************************************************************/
/*!
\file   DemoWrapPosition.h
\author Hun Yang
\par    email: hun.yang8456@gmail.com
\par    GAM150 demo
\date   2019/04/30

Component to wrap object's position, when it is in outside of screen.
*/
/******************************************************************************/
#pragma once
#include "Component.h"

class Transform;
class DemoWrapPosition : public Component
{
public:
    DemoWrapPosition();
    ~DemoWrapPosition();
    virtual void Initialize     ()              override;
    virtual void Update         (float dt)      override;
private:
public:
    float           mPositionOffest;    // position offset to wrap object
private:
    Transform*      mTransform;         // pointer to the owner's transform
};
