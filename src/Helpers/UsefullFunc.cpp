#include "UsefullFunc.h"
#include <cmath>
#include <stdlib.h>
namespace AnoukhFun
{
    float Damp(float current, float target, float smoothTime, float deltaTime)
    {
        return std::lerp(current, target, 1 - pow(smoothTime, deltaTime));
    }

    int RandomInt(int min, int max)
    {
        return rand() % (max - min + 1) + min;
    }

    float RandomFloat(float min, float max)
    {
        return min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max-min)));
    }
}
