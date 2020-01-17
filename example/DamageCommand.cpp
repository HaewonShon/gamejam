#include "DamageCommand.h"
#include "CustomBaseObject.h"
#include "DemoPlayerController.h"

DamageCommand::DamageCommand():
    Command(eCommandTypes::DamageCommand),
    mTarget(nullptr),
    mDamage(0)
{
}

DamageCommand::~DamageCommand()
{
    mTarget = nullptr;
}

void DamageCommand::Execute()
{
    if (!mTarget)
        return;
    DemoPlayerController* player;
    mTarget->GetComponent(eComponentTypes::DemoPlayerController, player);
    if (mDamage >= 0)
    {
        player->ApplyDamage(mDamage);
    }
    else
    {
        player->RestoreHealth(-mDamage);
    }
}
