/******************************************************************************/
/*!
\file   DemoCameralogic.h
\author Hun Yang
\par    email: hun.yang8456@gmail.com
\par    GAM150 demo
\date   2019/04/28

It is component to chase player's position
*/
/******************************************************************************/
#pragma once
#include "Component.h"
#include <Box2D/Common/b2Math.h>
#include "CustomPhysics.h"

// enum class for 'DemoChasePlayer' component state
enum class eDemoChaseEnemyState
{
    Normal,
    Chase,
    Back,
    Dead
};

class CustomBaseObject;
class DemoEnemySpawner;
class DemoTopdownController;
class DemoPlayerController;
class DemoChasePlayer : public Component
{
public:
    DemoChasePlayer();
    ~DemoChasePlayer();
    virtual void Initialize()       override;
    virtual void Update(float dt)   override;
private:
    bool detectPlayer       (bool saveData);
    void chaseUpdate        ();
    void backUpdate         (float dt);
public:
    float                   mSpeed;                 // Chase speed
    float                   mDetectRadius;          // radius for detection area
    float                   mDeathCount;            // Death delay second
private:
    CustomPhysics *         mPhysics;               // pointer to the object's custom physics component
    eDemoChaseEnemyState    mState;                 // Chase enemy state
    CustomBaseObject*       mPlayer;                // pointer to the player object
    DemoTopdownController*  mTopdownController;     // pointer to component for 'Topdown' controller 
    DemoPlayerController*   mPlatformerController;  // pointer to component for 'Platformer' controller 
    float                   mTimer;                 // timer
    b2Vec2                  mInitialVelocity;       // Initial velocity
    b2Vec2                  mReturnPositoin;        // position to return
    b2Vec2                  mReturnStartPosition;   // position starting return
};
