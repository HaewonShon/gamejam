#pragma once
#include "Command.h"
#include "engine/Transform.h"

class CustomBaseObject;
class CheckPointCommand : public Command
{
public:
    CheckPointCommand();
    ~CheckPointCommand();
    virtual void Execute() override;
private:
public:
    Transform*          mTransform;
    CustomBaseObject*   mTarget;
private:
};
