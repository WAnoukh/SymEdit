#pragma once
#include "TextureDrawerBase.h"

class Pen : public TextureDrawerBase
{
public:
    
    virtual void Apply(Texture& texture, ViewPort& viewPort, float mouseX, float mouseY);

private:

    int size = 10;
    unsigned char color[4]= {255,0,0,255};
    
};
