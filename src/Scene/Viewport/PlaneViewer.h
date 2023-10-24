#pragma once
#include "ViewPortBase.h"

class PlaneViewer : public ViewPortBase
{
public:
    void Init() override;
    void RenderUI() override;

    void Tick(float deltaTime) override;

    bool ScreenToTexture(const float x, const float y, float& outX, float& outY) override;

    
};
