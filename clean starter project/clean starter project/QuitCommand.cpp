#include "QuitCommand.h"
#include "engine/State.h"
#include "CommonLevel.h"

QuitCommand::QuitCommand():
    Command(eCommandTypes::QuitCommand)
{
}

QuitCommand::~QuitCommand()
{
}

void QuitCommand::Execute()
{
    State::sCurrentState->m_game->Quit();
}
