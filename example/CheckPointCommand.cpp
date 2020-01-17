#include "CheckPointCommand.h"
#include "CustomBaseObject.h"
#include "DemoPlayerController.h"

CheckPointCommand::CheckPointCommand():
    Command(eCommandTypes::CheckPointCommand),
    mTransform(nullptr),
    mTarget(nullptr)
{
}

CheckPointCommand::~CheckPointCommand()
{
}

void CheckPointCommand::Execute()
{
    if (!mTransform || !mTarget)
        return;

    DemoPlayerController::sStartPosition.Set(
        mTransform->position.x,
        mTransform->position.y - mTransform->GetHalfScale().y + mTarget->transform.GetHalfScale().y);
}
