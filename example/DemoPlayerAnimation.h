/******************************************************************************/
/*!
\file   DemoPlayerAnimation.h
\author Hun Yang
\par    email: hun.yang8456@gmail.com
\par    GAM150 demo
\date   2019/04/28

Based on 'DemoPlayerController' component's state, change Sprite's image
*/
/******************************************************************************/
#pragma once
#include "Component.h"

class CustomSprite;
class DemoPlatformerController;
class DemoPlayerAnimation : public Component
{
public:
    DemoPlayerAnimation();
    ~DemoPlayerAnimation();
    virtual void Initialize() override;
    virtual void Update(float dt) override;
private:
    void createCustomSprite(CustomSprite*& sprite, std::string filePath, bool isAnimation = false, unsigned frames = 0, float speed = 0);
public:
    std::string                 mPlayerStandFile;   // string for plaeyr stand file path
    std::string                 mPlayerWalkFile;    // string for plaeyr walk file path
    std::string                 mPlayerJumpFile;    // string for plaeyr jump file path
private:
    DemoPlatformerController*   mController;        // pointer to the component of platformer controller
    CustomSprite*               mPlayerStand;       // pointer to the custom sprite holding player stand image info
    CustomSprite*               mPlayerWalk;        // pointer to the custom sprite holding player walk image info
    CustomSprite*               mPlayerJump;        // pointer to the custom sprite holding player jump image info
};
