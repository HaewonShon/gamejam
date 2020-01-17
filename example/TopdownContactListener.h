/******************************************************************************/
/*!
\file   TopdownContactListener.h
\author Hun Yang
\par    email: hun.yang8456@gmail.com
\par    GAM150 demo
\date   2019/04/28

Custom contact listener fot topdown demo.
It must be used with Customphysics!!
*/
/******************************************************************************/
#pragma once
#include "engine/ContactListener.h"


class TopdownContactListener : public b2ContactListener
{
public:
    ~TopdownContactListener();
    // Called when two fixtures begin to touch.
    void BeginContact   (b2Contact* contact)    override;
    // Called when two fixtures cease to touch.
    void EndContact     (b2Contact* contact)    override;
};
