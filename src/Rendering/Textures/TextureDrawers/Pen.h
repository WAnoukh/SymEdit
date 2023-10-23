#pragma once
#include "TextureDrawerBase.h"

class Pen : public TextureDrawerBase
{
public:
    
    virtual void Apply(Texture& texture, TextureEditor& viewPort, float mouseX, float mouseY) override;

    virtual void RenderUI() override;
    
    void SetInterpolate(bool inInterpolate);

    void Draw(int x, int y, Texture& texture);

private:
    bool interpolate = false;
    bool ignoreNextInterpolate = false;
    int lastPixelX = 0;
    int lastPixelY = 0;
    int size = 1;
    unsigned char color[4]= {255,0,0,255};
    float uiColor[3] = {255.0f,0.0f,0.0f};
};
