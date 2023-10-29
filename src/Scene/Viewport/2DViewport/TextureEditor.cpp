#include "TextureEditor.h"
#include <glad/glad.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include <GLFW/glfw3.h>

#include <stb_image.h>

#include "imgui_impl_opengl3_loader.h"
#include "../../../Application/Application.h"
#include "../../../Rendering/shader_s.h"


#include "../../../Rendering/TextureLoader.h"

TextureEditor::~TextureEditor()
{
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
}

void TextureEditor::Init()
{
    ViewPortBase::Init();
    constexpr float vertices[] = {
        // positions        // uv coord
        0.5f,  -0.5f, 0.0f, 1.0f, 1.0f, // top right
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, // bottom right
       -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, // bottom left
       -0.5f, -0.5f, 0.0f, 0.0f, 1.0f  // top left 
    };
    const unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    shader = new Shader("src/Rendering/Shaders/ViewPort/TextureEditor.vert", "src/Rendering/Shaders/ViewPort/TextureEditor.frag");

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

void TextureEditor::RenderViewPort()
{
    ViewPortBase::RenderViewPort();

    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    const Texture& texture = Application::GetInstance().GetActiveTexture();
    glBindTexture(GL_TEXTURE_2D, texture.GetTextureId());
    shader->use();
    float correctedScaleX, correctedScaleY;
    GetScreenZoom(correctedScaleX, correctedScaleY);
    shader->setVec2("scale", correctedScaleX,correctedScaleY);
    float correctedOffsetX, correctedOffsetY;
    GetScreenOffset(correctedOffsetX, correctedOffsetY);
    shader->setVec2("offset", correctedOffsetX, correctedOffsetY);
    shader->setFloat("time", glfwGetTime());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void TextureEditor::RenderUI()
{
    ViewPort2D::RenderUI();
    ImVec2 cursorPos = ImGui::GetCursorPos();
    ImVec2 windowPos = ImGui::GetWindowPos();
    const ImVec2 mousePos = ImGui::GetMousePos();
    ImVec2 texturePos;
    ScreenToTexture(mousePos.x, mousePos.y, texturePos.x, texturePos.y);
    //TODO: Erase this
    ImGui ::Begin("help tool");
    ImGui::Text("MousePos: %f %f", mousePos.x, mousePos.y);
    const ImVec2 viewPortPos = GetViewPortPos();
    ImGui::Text("MousePosRelative: %f %f", mousePos.x - viewPortPos.x,mousePos.y - viewPortPos.y);
    ImGui::Text("ViewPortPos: %f %f", viewPortPos.x, viewPortPos.y);
    ImGui::Text("TexturePos: %f %f", texturePos.x, texturePos.y);
    ImGui::End();
}

bool TextureEditor::ScreenToTexture(const float x, const float y, float& outX, float& outY)
{
    const auto viewPortPos = GetViewPortPos();
    const auto mouseLocalPos = ImVec2(x - viewPortPos.x, y - viewPortPos.y);
    const auto viewPortSize = GetViewPortSize();
    const auto mouseLocalPosNormalized = ImVec2(mouseLocalPos.x / viewPortSize.x, mouseLocalPos.y / viewPortSize.y);
    const auto mouseLocalPosNormalizedCentered = ImVec2(mouseLocalPosNormalized.x * 2.0f - 1.0f, mouseLocalPosNormalized.y * -2.0f + 1.0f);
    float correctedScaleX, correctedScaleY;
    GetScreenZoom(correctedScaleX, correctedScaleY);
    float correctedOffsetX, correctedOffsetY;
    GetScreenOffset(correctedOffsetX, correctedOffsetY);
    const auto mouseTexturePos = ImVec2(
        mouseLocalPosNormalizedCentered.x / correctedScaleX + correctedOffsetX +0.5f,
        - (mouseLocalPosNormalizedCentered.y) / correctedScaleY - correctedOffsetY +0.5f
        );
    outX = mouseTexturePos.x;
    outY = mouseTexturePos.y;

    if(outX < 0.0f || outX > 1.0f || outY < 0.0f || outY > 1.0f)
    {
        return false;
    }
    
    return true;
}

void TextureEditor::GetScreenZoom(float& x, float& y)
{
    float zoom = GetDisplayedZoom();
    ImVec2 viewPortSize = GetViewPortSize();
    float ratio = viewPortSize.x / viewPortSize.y;
    Application& app = Application::GetInstance();
    Texture& texture = app.GetActiveTexture();
    float textureRatio = static_cast<float>(texture.GetWidth()) / static_cast<float>(texture.GetHeight());
    x = zoom * textureRatio;
    y = zoom * ratio;
}

void TextureEditor::GetScreenOffset(float& x, float& y)
{
    ImVec2 offset = GetDisplayedOffset();
    ImVec2 viewPortSize = GetViewPortSize();
    x = -offset.x / (viewPortSize.x / 2);
    y = offset.y / (viewPortSize.y / 2);
}
