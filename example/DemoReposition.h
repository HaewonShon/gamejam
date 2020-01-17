/******************************************************************************/
/*!
\file   DemoReposition.h
\author Hun Yang
\par    email: hun.yang8456@gmail.com
\par    GAM150 demo
\date   2019/04/26


Reposition component
It update object's position with base point as the center.
*/
/******************************************************************************/
#pragma once
#include "Component.h"
#include <Box2D/Common/b2Math.h>

// enum class for resposition base type
enum class DemoRepositionBase
{
    TopLeft,
    TopRight,
    BottomLeft,
    BottomRight
};

class DemoReposition : public Component
{
public:
    DemoReposition();
    ~DemoReposition();
    virtual void    Initialize  ()                          override;
    virtual void    Update      (float dt)                  override;
    void            SetBase     (DemoRepositionBase base);
private:
public:
private:
    DemoRepositionBase      mBase;
    b2Vec2                  mPositionByBase;
};
