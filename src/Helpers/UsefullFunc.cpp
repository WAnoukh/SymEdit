#include "UsefullFunc.h"
#include <cmath>
namespace AnoukhFun
{
    float Damp(float current, float target, float smoothTime, float deltaTime)
    {
        return std::lerp(current, target, 1 - pow(smoothTime, deltaTime));
    }
    
}
