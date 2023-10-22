#include "ViewPort.h"
#include <glad/glad.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

#include <stb_image.h>

#include "imgui_impl_opengl3_loader.h"
#include "../Rendering/shader_s.h"

#include "../Helpers/UsefullFunc.h"
#include "../Rendering/TextureLoader.h"

ViewPort::ViewPort()= default;

ViewPort::~ViewPort()
{
    glDeleteFramebuffers(1, &FBO);
    glDeleteTextures(1,&viewPortTexture);
}

void ViewPort::Init()
{
    glGenFramebuffers(1, &FBO);
    glGenTextures(1, &viewPortTexture);
    float vertices[] = {
        // positions        // uv coord
        0.5f,  -0.5f, 0.0f, 1.0f, 1.0f, // top right
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, // bottom right
       -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, // bottom left
       -0.5f, -0.5f, 0.0f, 0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    shader = new Shader("src/Rendering/Shaders/ViewPort.vert", "src/Rendering/Shaders/ViewPort.frag");

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    LoadTexture();
    texture.CreateBlankTexture(100, 50, GL_RGB);
    texture.GenerateOpenGlTexture();
    texture.SendDataToOpenGl();
}

void ViewPort::PreRenderViewPort()
{
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    

    int width = static_cast<int>(lastSize.x), height = static_cast<int>(lastSize.y);

    glViewport(0, 0, width, height);
    
    glBindTexture(GL_TEXTURE_2D, viewPortTexture);
  
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width , height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, viewPortTexture, 0);

    texture.SendDataToOpenGl();
}

void ViewPort::RenderViewPort()
{
    PreRenderViewPort();
    
    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.GetTextureId());
    shader->use();
    float correctedScaleX, correctedScaleY;
    GetVertexScale(correctedScaleX, correctedScaleY);
    shader->setVec2("scale", correctedScaleX,correctedScaleY);
    float correctedOffsetX, correctedOffsetY;
    GetVertexOffset(correctedOffsetX, correctedOffsetY);
    shader->setVec2("offset", correctedOffsetX, correctedOffsetY);
    shader->setFloat("time", glfwGetTime());
    
    glClearColor(0.20784313725490197f, 0.1843137254901961f, 0.26666666666666666, 1.00f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ViewPort::RenderUI()
{
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
    ImVec2 mousePos = ImGui::GetMousePos();
    ImVec2 texturePos;
    ScreenToTexture(mousePos.x, mousePos.y, texturePos.x, texturePos.y);

    //TODO: Erase this
    ImGui::Image((ImTextureID)viewPortTexture, windowSize , ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();
    ImGui::PopStyleVar();
    ImGui ::Begin("help tool");
    ImGui::Text("MousePos: %f %f", mousePos.x, mousePos.y);
    ImGui::Text("ViewPortPos: %f %f", viewPortPos.x, viewPortPos.y);
    ImGui::Text("TexturePos: %f %f", texturePos.x, texturePos.y);
    ImGui::End();
}

void ViewPort::Tick(float deltaTime)
{
    zoom = AnoukhFun::Damp(zoom, targetZoom, 0.0f, deltaTime);
    const glm::vec2 vPanOffset = glm::vec2(panOffset.x, panOffset.y);
    const glm::vec2 vTargetPanOffset = glm::vec2(targetPanOffset.x, targetPanOffset.y);
    const auto newOffset = AnoukhFun::Damp<glm::vec2>( vPanOffset , vTargetPanOffset, 0.00000001f, deltaTime);
    panOffset = ImVec2(targetPanOffset.x, targetPanOffset.y);
    RenderViewPort();
    unsigned char col[3] = {static_cast<unsigned char>(AnoukhFun::RandomInt(0,255)),
        static_cast<unsigned char>(AnoukhFun::RandomInt(0,255)),
        static_cast<unsigned char>(AnoukhFun::RandomInt(0,255))};
    //texture.EditPixel(AnoukhFun::RandomInt(0, texture.GetWidth()-1), AnoukhFun::RandomInt(0, texture.GetHeight()-1), col );
}

void ViewPort::SetZoom(float inZoom)
{
    targetZoom = inZoom;
}

float ViewPort::GetZoom()
{
    return zoom;
}

bool ViewPort::IsWindowHovered()
{
    return isWindowHovered;
}

const char* ViewPort::GetGuiName()
{
    return guiName; 
}

void ViewPort::StartPanning(const float x, const float y)
{
    startPan = ImVec2(x,y);
    targetPanOffset= ImVec2(0.0f,0.0f);
    isPanning = true;
}

void ViewPort::SetPanOffset(const float x, const float y)
{
    if(isPanning)
    {
        targetPanOffset = ImVec2(startPan.x - x,startPan.y - y);
    }
}

void ViewPort::StopPanning(bool savePan)
{
    isPanning = false;
    if (savePan)
    {
        offset = ImVec2(offset.x + targetPanOffset.x, offset.y + targetPanOffset.y);
    }
    panOffset = ImVec2(panOffset.x - targetPanOffset.x,panOffset.y- targetPanOffset.y);
    targetPanOffset = ImVec2(0.0f,0.0f);
}

bool ViewPort::IsPanning() const
{
    return isPanning;
}

bool ViewPort::ScreenToTexture(const float x, const float y, float& outX, float& outY)
{
    ImVec2 mouseLocalPos = ImVec2(x - viewPortPos.x, y - viewPortPos.y);
    ImVec2 mouseLocalPosNormalized = ImVec2(mouseLocalPos.x / lastSize.x, mouseLocalPos.y / lastSize.y);
    ImVec2 mouseLocalPosNormalizedCentered = ImVec2(mouseLocalPosNormalized.x * 2.0f - 1.0f, mouseLocalPosNormalized.y * -2.0f + 1.0f);
    float correctedScaleX, correctedScaleY;
    GetVertexScale(correctedScaleX, correctedScaleY);
    float correctedOffsetX, correctedOffsetY;
    GetVertexOffset(correctedOffsetX, correctedOffsetY);
    ImVec2 mouseTexturePos = ImVec2((mouseLocalPosNormalizedCentered.x - correctedOffsetX) / correctedScaleX +0.5f ,0.5f - (mouseLocalPosNormalizedCentered.y- correctedOffsetY) / correctedScaleY);
    outX = mouseTexturePos.x;
    outY = mouseTexturePos.y;

    if(outX < 0.0f || outX > 1.0f || outY < 0.0f || outY > 1.0f)
    {
        return false;
    }
    
    return true;
}

Texture& ViewPort::GetTexture()
{
    return texture;
}

void ViewPort::LoadTexture()
{
    canvasTexture = loadTexture("src/testcoloris.jpg");
}

void ViewPort::GetVertexScale(float& x, float& y)
{
    float ratio = lastSize.x / lastSize.y;
    float textureRatio = static_cast<float>(texture.GetWidth()) / static_cast<float>(texture.GetHeight());
    x = zoom * textureRatio;
    y = zoom * ratio;
}

void ViewPort::GetVertexOffset(float& x, float& y)
{
    x = (-(offset.x + panOffset.x)) / (lastSize.x / 2);
    y = (offset.y + panOffset.y) / (lastSize.y / 2);
}
