#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../ViewPortBase.h"

class ViewPort2D : public ViewPortBase
{
public:
    ViewPort2D(const char* name = "ViewPort2D") : ViewPortBase(name){}

    //Zoom
    void SetZoom(float inZoom);
    float GetDisplayedZoom() const;
    
    //Panning
    void StartPanning(const float x, const float y);
    void ApplyPanning(const float x, const float y);
    void StopPanning(bool savePan = true);
    bool IsPanning() const;
    ImVec2 GetDisplayedOffset() const;    

    void Tick(float deltaTime) override;
    void RenderUI() override;

    void ScrollCallBackEvent(GLFWwindow* window, bool guiWantToCapture, double xoffset, double yoffset) override;

    void MouseButtonCallBackEvent(GLFWwindow* window, bool guiWantToCapture, int button, int action, int mods) override;

    void MousePositionCallBackEvent(GLFWwindow* window, bool guiWantToCapture, double xPos, double yPos) override;

protected:
    virtual void GetScreenZoom(float& x, float& y) = 0;

    virtual void GetScreenOffset(float& x, float& y) = 0;
    
private:
    // Panning
    bool isPanning = false;
    ImVec2 lastMousePos = ImVec2(0.0f,0.0f);
    ImVec2 displayedOffset = ImVec2(0.0f,0.0f);
    ImVec2 targetPanOffset = ImVec2(0.0f,0.0f);

    // Zoom
    float displayedZoom = 1.0f;
    float targetZoom = 1.0f;
};
