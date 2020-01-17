#pragma once

namespace MathUtils
{
    float   RadianToDegree    (float radian);
    float   DegreeToRadian    (float degree);
    float   Lerp              (float start, float end, float value);
    float   Wrap              (float value, float min, float max);

    int     GetRandomInt      (int min, int max);
    float   GetRandomFloat    (float min, float max);
}