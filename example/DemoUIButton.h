/******************************************************************************/
/*!
\file   DemoUIButton.h
\author Hun Yang
\par    email: hun.yang8456@gmail.com
\par    GAM150 demo
\date   2019/04/26


This is UI Button component, which is triggered by mouse clicking.
*/
/******************************************************************************/
#pragma once
#include "Component.h"

class Command;
class CustomSprite;
class DemoUIButton : public Component
{
public:
    DemoUIButton();
    ~DemoUIButton();
    virtual void Initialize     ()              override;
    virtual void Update         (float dt)      override;

private:
public:
    Command*        mButtonEvent;           // command for button event
    std::string     mDefaultSpriteFile;     // default sprite file path
    std::string     mHoveredSpriteFile;     // hovered sprite file path
private:
    CustomSprite*   mDefaultSprite;         // default sprite image
    CustomSprite*   mHoveredSprite;         // hovered sprite image
};
