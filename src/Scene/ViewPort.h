#pragma once
#include "../../third_parties/imgui/imgui.h"
#include "../Rendering/Textures/Texture.h"

class Shader;


class ViewPort
{
public:
    ViewPort();
    ~ViewPort();

    void Init();
    void PreRenderViewPort();
    void RenderViewPort();
    void RenderUI();

    void Tick(float deltaTime);

    void SetZoom(float inZoom);
    float GetZoom();

    bool IsWindowHovered();

    const char* GetGuiName();

    void StartPanning(const float x, const float y);

    void SetPanOffset(const float x, const float y);

    void StopPanning(bool savePan = true);

    bool IsPanning() const;

private:
    const char* guiName = "Viewport";
    Texture texture;
    unsigned int viewPortTexture, canvasTexture;
    unsigned int VBO, VAO, EBO, FBO;
    Shader* shader;
    ImVec2 lastSize = ImVec2(0,0);
    bool isWindowHovered = false;

    // Panning
    bool isPanning = false;
    ImVec2 startPan = ImVec2(0.0f,0.0f);
    ImVec2 offset = ImVec2(0.0f,0.0f);
    ImVec2 panOffset= ImVec2(0.0f,0.0f);
    ImVec2 targetPanOffset = ImVec2(0.0f,0.0f);

    // Zoom
    float zoom = 1.0f;
    float targetZoom = 1.0f;

    void LoadTexture();
};
