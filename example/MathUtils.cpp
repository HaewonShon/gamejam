#include "MathUtils.h"
#include <SDL2/SDL_stdinc.h>
#include <cstdlib>


namespace
{
    constexpr float radianToDegree      = (180.f / (float)M_PI);
    constexpr float degreeToRadian      = ((float)M_PI / 180.f);
}

float MathUtils::RadianToDegree(float radian)
{
    return radian * radianToDegree;
}

float MathUtils::DegreeToRadian(float degree)
{
    return degree * degreeToRadian;
}


float MathUtils::Lerp(float start, float end, float value)
{
    return (1.f - value) * start + value * end;
}

float MathUtils::Wrap(float value, float min, float max)
{
    if (value >= max)
    {
        value = min;
    }
    else if (value < min)
    {
        value = max;
    }

    return value;
}

int MathUtils::GetRandomInt(int min, int max)
{
    int result = rand() % (max - min) + 1;
    return result + min;
}

float MathUtils::GetRandomFloat(float min, float max)
{
    float result = rand() / static_cast<float>(RAND_MAX);
    result *= (max - min);
    return result + min;
}
