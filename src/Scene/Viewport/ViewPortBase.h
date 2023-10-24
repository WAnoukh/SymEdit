#pragma once
#include "../../third_parties/imgui/imgui.h"


class ViewPortBase
{
public:
    ViewPortBase() : guiName("ViewportBase")
    {
    }

    virtual ~ViewPortBase() {}

    virtual void Init() = 0;
    virtual void RenderUI();
    void PreRenderViewPort();
    virtual void RenderViewPort();

    virtual void Tick(float deltaTime) = 0;

    virtual const char* GetGuiName();

    virtual bool ScreenToTexture(const float x, const float y, float& outX, float& outY) = 0;
    
protected:
    const char* guiName;
    ImVec2 lastSize = ImVec2(0,0);
    ImVec2 viewPortPos = ImVec2(0,0);
    unsigned int viewPortTexture = 0;
    unsigned int FBO = 0;
    unsigned int VAO = 0;
    
    bool isWindowHovered = false;
};
