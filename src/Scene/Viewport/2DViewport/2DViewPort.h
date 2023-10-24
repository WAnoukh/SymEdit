#pragma once
#include "../ViewPortBase.h"

class ViewPort2D : public ViewPortBase
{
public:
    virtual void SetZoom(float inZoom);
    virtual float GetZoom();
    virtual void StartPanning(const float x, const float y);
    virtual void StopPanning(bool savePan = true);
    virtual void SetPanOffset(const float x, const float y);
    virtual bool IsPanning() const;
    virtual ImVec2 GetOffset() const;

    void Tick(float deltaTime) override;
    
private:
    // Panning
    bool isPanning = false;
    ImVec2 startPan = ImVec2(0.0f,0.0f);
    ImVec2 offset = ImVec2(0.0f,0.0f);
    ImVec2 panOffset= ImVec2(0.0f,0.0f);
    ImVec2 targetPanOffset = ImVec2(0.0f,0.0f);

    // Zoom
    float zoom = 1.0f;
    float targetZoom = 1.0f;
};
