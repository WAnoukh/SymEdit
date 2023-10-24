#include "2DViewPort.h"
#include "../../../Helpers/UsefullFunc.h"

#include <glm/vec2.hpp>

void ViewPort2D::SetZoom(float inZoom)
{
    targetZoom = inZoom;
}

float ViewPort2D::GetZoom()
{
    return zoom;
}

void ViewPort2D::StartPanning(const float x, const float y)
{
    startPan = ImVec2(x,y);
    targetPanOffset= ImVec2(0.0f,0.0f);
    isPanning = true;
}

void ViewPort2D::SetPanOffset(const float x, const float y)
{
    if(isPanning)
    {
        targetPanOffset = ImVec2(startPan.x - x,startPan.y - y);
    }
}

void ViewPort2D::StopPanning(bool savePan)
{
    isPanning = false;
    if (savePan)
    {
        offset = ImVec2(offset.x + targetPanOffset.x, offset.y + targetPanOffset.y);
    }
    panOffset = ImVec2(panOffset.x - targetPanOffset.x,panOffset.y- targetPanOffset.y);
    targetPanOffset = ImVec2(0.0f,0.0f);
}

bool ViewPort2D::IsPanning() const
{
    return isPanning;
}

ImVec2 ViewPort2D::GetOffset() const
{
    return ImVec2(offset.x + panOffset.x, offset.y + panOffset.y);
}

void ViewPort2D::Tick(float deltaTime)
{
    zoom = AnoukhFun::Damp(zoom, targetZoom, 0.0f, deltaTime);
    const glm::vec2 vPanOffset = glm::vec2(panOffset.x, panOffset.y);
    const glm::vec2 vTargetPanOffset = glm::vec2(targetPanOffset.x, targetPanOffset.y);
    const auto newOffset = AnoukhFun::Damp<glm::vec2>( vPanOffset , vTargetPanOffset, 0.00000001f, deltaTime);
    panOffset = ImVec2(targetPanOffset.x, targetPanOffset.y);
}
