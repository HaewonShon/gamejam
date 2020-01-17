#pragma once
#include "CommandTypes.h"

class Command
{
public:
    Command(eCommandTypes type);
    virtual ~Command() {};
    virtual void Execute() = 0;
private:
    eCommandTypes mType;
};
