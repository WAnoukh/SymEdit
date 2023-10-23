#pragma once
#include "ViewPortBase.h"
#include "../../third_parties/imgui/imgui.h"
#include "../../Rendering/Textures/Texture.h"

class Shader;


class TextureEditor : public ViewPortBase
{
public:
    TextureEditor() { guiName = "TextureEditor"; }

    ~TextureEditor() override;

    void Init() override;
    void PreRenderViewPort();
    void RenderViewPort();
    void RenderUI() override;

    void Tick(float deltaTime) override;

    void SetZoom(float inZoom);
    
    float GetZoom();

    bool IsWindowHovered();

    void StartPanning(const float x, const float y);

    void SetPanOffset(const float x, const float y);

    void StopPanning(bool savePan = true);

    bool IsPanning() const;

    bool ScreenToTexture(const float x, const float y, float& outX, float& outY) override;

    Texture& GetTexture();

private:
    Texture texture;
    unsigned int canvasTexture;
    unsigned int VBO, EBO;
    Shader* shader;

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

    void GetVertexScale(float& x, float& y);

    void GetVertexOffset(float& x, float& y);
};
