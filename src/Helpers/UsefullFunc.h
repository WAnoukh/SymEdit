#pragma once
#include <cmath>

namespace AnoukhFun
{
    float Damp(float current, float target, float smoothTime, float deltaTime);

    template <typename T>
    T Lerp(T a, T b, float t)
    {
        return a + t * (b - a);
    }

    template <typename T>
    T Damp(T current, T target, float smoothTime, float deltaTime)
    {
        return Lerp(current, target, 1 - pow(smoothTime, deltaTime));
    }
}
