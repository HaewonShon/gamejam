/******************************************************************************/
/*!
\file   DemoCameralogic.h
\author Hun Yang
\par    email: hun.yang8456@gmail.com
\par    GAM150 demo
\date   2019/04/23

Camera Logic for platformer demo
It chase player, rotate screen, and zoom in.
*/
/******************************************************************************/
#pragma once
#include "Component.h"
#include <Box2D/Common/b2Math.h>

// enum class for Demo camera logic's state
enum class eDemoCameraState
{
    Normal,
    Rotate,
    ZoomIn
};
class Camera;
class DemoPlayerController;

class DemoCameraLogic : public Component
{
public:
    DemoCameraLogic();
    ~DemoCameraLogic();
    virtual void Initialize     ()                      override;
    virtual void Update         (float dt)              override;
    // Set camera logic's state
    void SetCameraState         (eDemoCameraState state);
    // Syncronize Camera's position with Target's position 
    void SyncCameraWithTarget   ();
private:
    eDemoCameraState    mState;             // Camera Logic's state
    Camera *            mCamera;            // pointer to the camera
    Object *            mTarget;            // pointer to the target object
    float               mTimer;             // timer to check passed time
    b2Vec2              mPositionOffset;    // offset from target's position
};
