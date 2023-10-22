#pragma once

class Texture;
class ViewPort;

class TextureDrawerBase
{
    virtual void Apply(Texture& texture, ViewPort& viewPort, float mouseX, float mousey) = 0;
};
