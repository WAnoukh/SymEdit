#include "ViewPortBase.h"
#include <glad/glad.h>
#include "imgui.h"
#include <GLFW/glfw3.h>

ViewPortBase::~ViewPortBase()
{
    glDeleteFramebuffers(1, &FBO);
    glDeleteTextures(1,&viewPortTexture);
}

void ViewPortBase::Init()
{
    glGenFramebuffers(1, &FBO);
    glGenTextures(1, &viewPortTexture);
}

void ViewPortBase::RenderUI()
{
    RenderViewPort();
    // Set all margins to 0 for the ImGui window
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin(guiName);
    isWindowHovered = ImGui::IsWindowHovered();
    ImVec2 windowSize = ImGui::GetContentRegionAvail();
    if(windowSize.x != lastSize.x || windowSize.y != lastSize.y)
    {
        lastSize = windowSize;
    }
    ImVec2 cursorPos = ImGui::GetCursorPos();
    ImVec2 windowPos = ImGui::GetWindowPos();
    viewPortPos = ImVec2(cursorPos.x + windowPos.x, cursorPos.y + windowPos.y);
    ImGui::Image((ImTextureID)viewPortTexture, windowSize , ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();
    ImGui::PopStyleVar();
}

void ViewPortBase::PreRenderViewPort()
{
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    int width = static_cast<int>(lastSize.x), height = static_cast<int>(lastSize.y);

    glViewport(0, 0, width, height);
    
    glBindTexture(GL_TEXTURE_2D, viewPortTexture);
  
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width , height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, viewPortTexture, 0);

    glClearColor(0.20784313725490197f, 0.1843137254901961f, 0.26666666666666666, 1.00f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void ViewPortBase::RenderViewPort()
{
    PreRenderViewPort();
}

bool ViewPortBase::IsWindowHovered()
{
    return isWindowHovered;
}

const char* ViewPortBase::GetGuiName()
{
    return guiName;
}

ImVec2 ViewPortBase::GetViewPortPos()
{
    return viewPortPos;
}

ImVec2 ViewPortBase::GetViewPortSize()
{
    return lastSize;
}

