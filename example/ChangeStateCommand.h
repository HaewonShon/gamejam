#pragma once
#include "Command.h"
#include "CommonLevel.h"

class ChangeStateCommand : public Command
{
public:
    ChangeStateCommand();
    ~ChangeStateCommand();
    virtual void Execute() override;
public:
    Level_ID mChangeLevel;
};
