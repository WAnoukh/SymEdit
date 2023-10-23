#pragma once

class Texture;
class TextureEditor;

class TextureDrawerBase
{
    virtual void Apply(Texture& texture, TextureEditor& viewPort, float mouseX, float mousey) = 0;

    virtual void RenderUI() = 0;
};
