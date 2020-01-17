/******************************************************************************/
/*!
\file   DemoRescale.h
\author Hun Yang
\par    email: hun.yang8456@gmail.com
\par    GAM150 demo
\date   2019/04/26


Rescale component
It update object's scale based on current screen width and height
*/
/******************************************************************************/
#pragma once
#include "Component.h"
#include <Box2D/Common/b2Math.h>

class DemoRescale : public Component
{
public:
    DemoRescale();
    ~DemoRescale();
    virtual void Initialize() override;
    virtual void Update(float dt) override;
private:
    b2Vec2          mInitialScale;
};
