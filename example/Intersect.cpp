#include "Intersect.h"

bool Intersect::CircleToCircle(const b2Vec2& center1, float radius1, const b2Vec2& center2, float radius2)
{
    float distanceSquared = b2Vec2(center2 - center1).LengthSquared();
    return (distanceSquared <= (radius1 * radius1 + radius2 * radius2));
}

bool Intersect::PointToBox(const b2Vec2& point, const b2Vec2& boxCenter, const b2Vec2& boxScale)
{
    // Get half scale
    b2Vec2 halfScale        (boxScale.x * 0.5f, boxScale.y * 0.5f);


    // move point to box model space
    b2Vec2 subPosition(
        point.x - boxCenter.x,
        point.y - boxCenter.y);

    return (
        (subPosition.x <= halfScale.x) &&
        (subPosition.x >= -halfScale.x) &&
        (subPosition.y <= halfScale.y) &&
        (subPosition.y >= -halfScale.y));
}
