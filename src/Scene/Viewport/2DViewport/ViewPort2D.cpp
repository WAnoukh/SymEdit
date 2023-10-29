#include "ViewPort2D.h"

#include <string>

#include "../../../Helpers/UsefullFunc.h"

#include <glm/glm.hpp>



void ViewPort2D::SetZoom(float inZoom)
{
    targetZoom = inZoom;
}

float ViewPort2D::GetDisplayedZoom() const 
{
    return displayedZoom;
}

void ViewPort2D::StartPanning(const float x, const float y)
{
    lastMousePos = {x,y};
    //startPan = ImVec2(x,y);
    //targetPanOffset= ImVec2(0.0f,0.0f);
    isPanning = true;
}

void ViewPort2D::ApplyPanning(const float x, const float y)
{
    ImVec2 screenZoom;
    GetScreenZoom(screenZoom.x, screenZoom.y);
    targetPanOffset = {
                        targetPanOffset.x + x / screenZoom.x,
                        targetPanOffset.y + y / screenZoom.y
                        }; 
}

void ViewPort2D::StopPanning(bool savePan)
{
    isPanning = false;
    //if (savePan)
    //{
    //    offset = ImVec2(offset.x + targetPanOffset.x, offset.y + targetPanOffset.y);
    //}
    //panOffset = ImVec2(panOffset.x - targetPanOffset.x,panOffset.y- targetPanOffset.y);
    //targetPanOffset = ImVec2(0.0f,0.0f);
}

bool ViewPort2D::IsPanning() const
{
    return isPanning;
}

ImVec2 ViewPort2D::GetDisplayedOffset() const
{
    return {displayedOffset.x, displayedOffset.y};
}

void ViewPort2D::Tick(float deltaTime)
{
    displayedZoom = AnoukhFun::Damp(displayedZoom, targetZoom, lerpSpeed, deltaTime);
    const glm::vec2 vPanOffset = glm::vec2(displayedOffset.x, displayedOffset.y);
    const glm::vec2 vTargetPanOffset = glm::vec2(targetPanOffset.x, targetPanOffset.y);
    const auto newOffset = AnoukhFun::Damp<glm::vec2>( vPanOffset , vTargetPanOffset, lerpSpeed, deltaTime);
    displayedOffset = {newOffset.x, newOffset.y};
}

void ViewPort2D::RenderUI()
{
    ViewPortBase::RenderUI();
    const std::string name = ("offsets %s" + std::string(GetGuiName()));
    ImGui::Begin(name.c_str());
    ImVec2 screenToTextPos;
    ScreenToTexture(ImGui::GetMousePos().x, ImGui::GetMousePos().y, screenToTextPos.x, screenToTextPos.y);
    ImGui::Text("dOffset: %f, %f", displayedOffset.x, displayedOffset.y);
    ImGui::Text("tOffset: %f, %f", targetPanOffset.x, targetPanOffset.y);
    ImGui::Text("TexturePos: %f, %f", screenToTextPos.x, screenToTextPos.y);
    //Create a button to call the recompile shader function
    ImGui::Button("Recompile Shaders");
    if (ImGui::IsItemClicked())
    {
        RecompileShaders();
    }
    ImGui::Button("Reset Zoom and Panning");
    if (ImGui::IsItemClicked())
    {
        targetZoom = 1.0f;
        targetPanOffset = ImVec2(0.0f,0.0f);
        lerpSpeed = defaultLerpSpeed;
    }

    ImGui::End();
}

void ViewPort2D::ScrollCallBackEvent(GLFWwindow* window, bool guiWantToCapture, double xoffset, double yoffset)
{
    if (IsWindowHovered())
    {
        lerpSpeed = 0.0f;
        SetZoom(GetDisplayedZoom() * (1.0f + static_cast<float>(yoffset)*0.1f));
        ImGui::SetWindowFocus(GetGuiName());
    }
}

void ViewPort2D::MouseButtonCallBackEvent(GLFWwindow* window, bool guiWantToCapture, int button, int action, int mods)
{
    if(button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        if(action == GLFW_PRESS)
        {
            if (IsWindowHovered() && !IsPanning())
            {
                lerpSpeed = 0.0f;
                ImVec2 mousePos = ImGui::GetMousePos();
                StartPanning(mousePos.x, mousePos.y);
                ImGui::SetWindowFocus(GetGuiName());
            }
        }
        else if(action == GLFW_RELEASE)
        {
            if(IsPanning())
            {
                StopPanning();
            }
        }
        return;
    }
}

void ViewPort2D::MousePositionCallBackEvent(GLFWwindow* window, bool guiWantToCapture, double xPos, double yPos)
{
    if(IsPanning())
    {
        ImVec2 mousePos = {static_cast<float>(xPos),static_cast<float>(yPos)};
        ApplyPanning(mousePos.x - lastMousePos.x, mousePos.y - lastMousePos.y);
        lastMousePos = mousePos;
        
        //SetPanOffset(mousePos.x, mousePos.y);
        //->targetPanOffset = ImVec2(startPan.x - x,startPan.y - y);
        ImGui::SetWindowFocus(GetGuiName());
    }
}

void ViewPort2D::RecompileShaders()
{
}
