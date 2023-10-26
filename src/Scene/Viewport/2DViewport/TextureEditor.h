#pragma once
#include "ViewPort2D.h"
#include "../ViewPortBase.h"
#include "../../third_parties/imgui/imgui.h"
#include "../../../Rendering/Textures/Texture.h"

class Shader;


class TextureEditor : public ViewPort2D
{
public:
    TextureEditor() : ViewPort2D("TextureEditor") {}

    ~TextureEditor() override;

    void Init() override;
    void RenderViewPort() override;
    void RenderUI() override;

    bool ScreenToTexture(const float x, const float y, float& outX, float& outY) override;


private:
    unsigned int VBO = 0;
    unsigned int EBO = 0;
    unsigned int VAO = 0;
    Shader* shader;

    void GetVertexScale(float& x, float& y);

    void GetVertexOffset(float& x, float& y);
};
