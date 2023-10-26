#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../ViewPortBase.h"

class ViewPort2D : public ViewPortBase
{
public:
    ViewPort2D(const char* name = "ViewPort2D") : ViewPortBase(name){}
    void SetZoom(float inZoom);
    float GetZoom();
    void StartPanning(const float x, const float y);
    void StopPanning(bool savePan = true);
    void SetPanOffset(const float x, const float y);
    bool IsPanning() const;
    ImVec2 GetOffset() const;

    void Tick(float deltaTime) override;

    void ScrollCallBackEvent(GLFWwindow* window, bool guiWantToCapture, double xoffset, double yoffset) override;

    void MouseButtonCallBackEvent(GLFWwindow* window, bool guiWantToCapture, int button, int action, int mods) override;

    void MousePositionCallBackEvent(GLFWwindow* window, bool guiWantToCapture, double xPos, double yPos) override;
    
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
