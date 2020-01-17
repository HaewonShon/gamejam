#include "RegisterCommands.h"
#include "engine/State.h"
#include "engine/CommandBuilder.h"
#include "ChangeStateCommand.h"
#include "QuitCommand.h"
#include "CheckPointCommand.h"
#include "DamageCommand.h"

void RegisterCommands()
{
    State::AddCommandBuilder(eCommandTypes::ChangeStateCommand,
                                new CommandTBuilder<ChangeStateCommand>);
    State::AddCommandBuilder(eCommandTypes::QuitCommand,
                                new CommandTBuilder<QuitCommand>);
    State::AddCommandBuilder(eCommandTypes::CheckPointCommand,
                                new CommandTBuilder<CheckPointCommand>);
    State::AddCommandBuilder(eCommandTypes::DamageCommand,
                                new CommandTBuilder<DamageCommand>);
}
