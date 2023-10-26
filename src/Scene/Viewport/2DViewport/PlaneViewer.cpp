#include "PlaneViewer.h"

void PlaneViewer::Init()
{
    
}

void PlaneViewer::RenderUI()
{
    ViewPort2D::RenderUI();
}

void PlaneViewer::Tick(float deltaTime)
{
    ViewPort2D::Tick(deltaTime);
}

bool PlaneViewer::ScreenToTexture(const float x, const float y, float& outX, float& outY)
{
    return true;
}
