#include "ChangeStateCommand.h"
#include "CommonLevel.h"

ChangeStateCommand::ChangeStateCommand():
    Command(eCommandTypes::ChangeStateCommand)
{
}

ChangeStateCommand::~ChangeStateCommand()
{

}

void ChangeStateCommand::Execute()
{
    State::m_game->Change(mChangeLevel);
}
