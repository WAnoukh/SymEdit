#pragma once
#include "2DViewPort.h"
#include "../ViewPortBase.h"
#include "../../third_parties/imgui/imgui.h"
#include "../../../Rendering/Textures/Texture.h"

class Shader;


class TextureEditor : public ViewPort2D
{
public:
    TextureEditor() { guiName = "TextureEditor"; }

    ~TextureEditor() override;

    void Init() override;
    void RenderViewPort() override;
    void RenderUI() override;

    bool IsWindowHovered();

    bool ScreenToTexture(const float x, const float y, float& outX, float& outY) override;

    Texture& GetTexture();

private:
    Texture texture;
    unsigned int canvasTexture;
    unsigned int VBO, EBO;
    Shader* shader;

    void LoadTexture();

    void GetVertexScale(float& x, float& y);

    void GetVertexOffset(float& x, float& y);
};
