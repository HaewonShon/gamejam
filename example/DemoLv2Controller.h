#pragma once
#include "Component.h"

class CustomPhysics;
class DemoLv2Controller : public Component
{
public:
    DemoLv2Controller();
    ~DemoLv2Controller();
    virtual void Initialize ()          override;
    virtual void Update     (float dt)  override;
private:
    CustomPhysics*      mPhysics;
};
