#pragma once
#include "Command.h"

class CustomBaseObject;
class DamageCommand : public Command
{
public:
    DamageCommand();
    ~DamageCommand();
    virtual void Execute() override;
private:
public:
    int                 mDamage;
    CustomBaseObject*   mTarget;
private:
};
