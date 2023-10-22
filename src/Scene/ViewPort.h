#pragma once
#include "../../third_parties/imgui/imgui.h"

class Shader;


class ViewPort
{
public:
    ViewPort();
    ~ViewPort();

    void Init();
    void PreViewPortRender();
    void ViewPortRender();
    void RenderUI();

    void SetZoom(float inZoom);
    float GetZoom();

    bool IsWindowHovered();

    const char* GetGuiName();

private:
    const char* guiName = "Viewport";
    unsigned int viewPortTexture, canvasTexture;
    unsigned int VBO, VAO, EBO, FBO;
    Shader* shader;
    ImVec2 lastSize = ImVec2(0,0);
    bool isWindowHovered = false;

    float zoom = 1.0f;

    void LoadTexture();
};
