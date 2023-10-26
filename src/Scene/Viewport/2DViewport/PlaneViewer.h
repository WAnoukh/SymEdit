#pragma once
#include "ViewPort2D.h"

class PlaneViewer : public ViewPort2D
{
public:
    void Init() override;
    void RenderUI() override;

    void Tick(float deltaTime) override;

    bool ScreenToTexture(const float x, const float y, float& outX, float& outY) override;
};
