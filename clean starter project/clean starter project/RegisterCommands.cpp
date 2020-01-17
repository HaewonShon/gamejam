#include "RegisterCommands.h"
#include "engine/State.h"
#include "engine/CommandBuilder.h"
#include "QuitCommand.h"

void RegisterCommands()
{
    State::AddCommandBuilder(eCommandTypes::QuitCommand,
                                new CommandTBuilder<QuitCommand>);
}

void UnregisterCommands()
{
    State::RemoveCommandBuilder(eCommandTypes::QuitCommand);
}
