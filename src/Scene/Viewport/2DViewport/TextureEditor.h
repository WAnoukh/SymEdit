#pragma once
#include "ViewPort2D.h"
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

private:
    unsigned int VBO, EBO;
    Shader* shader;

    void GetVertexScale(float& x, float& y);

    void GetVertexOffset(float& x, float& y);
};
