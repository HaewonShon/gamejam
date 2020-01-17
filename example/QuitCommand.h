#pragma once
#include "Command.h"

class QuitCommand : public Command
{
public:
    QuitCommand();
    ~QuitCommand();
    virtual void Execute() override;
public:
};
