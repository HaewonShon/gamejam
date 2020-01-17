#pragma once
#include <Box2D/Common/b2Math.h>

namespace Intersect
{
    bool CircleToCircle(const b2Vec2& center1, float radius1, const b2Vec2& center2, float radius2);
    bool PointToBox(const b2Vec2& point, const b2Vec2& boxCenter, const b2Vec2& boxScale);
}
