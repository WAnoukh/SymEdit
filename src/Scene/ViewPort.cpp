#include "ViewPort.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include <glad/glad.h>

#include "../Rendering/shader_s.h"
#include <stb_image.h>
#include "../Rendering/TextureLoader.h"

ViewPort::ViewPort()
{
}

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
        0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
       -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
       -0.5f,  0.5f, 0.0f, 0.0f, 1.0f  // top left 
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
}

void ViewPort::PreViewPortRender()
{
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    

    int width = static_cast<int>(lastSize.x), height = static_cast<int>(lastSize.y);

    glViewport(0, 0, width, height);
    
    glBindTexture(GL_TEXTURE_2D, viewPortTexture);
  
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width , height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, viewPortTexture, 0);
}

void ViewPort::ViewPortRender()
{
    PreViewPortRender();
    LoadTexture();
    
    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, canvasTexture);
    shader->use();
    shader->setVec2("scale", 1 * zoom, zoom * lastSize.x/lastSize.y);
    
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
        ViewPortRender();
    }
    ImGui::Image((ImTextureID)viewPortTexture, windowSize , ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();
    ImGui::PopStyleVar();
}

void ViewPort::SetZoom(float inZoom)
{
    zoom = inZoom;
    ViewPortRender();
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

void ViewPort::LoadTexture()
{
    canvasTexture = loadTexture("src/wall.jpg");
}
