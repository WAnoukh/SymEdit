#pragma once
#include "../../third_parties/imgui/imgui.h"


class ViewPortBase
{
public:
    ViewPortBase(const char* name = "ViewportBase") : guiName(name)
    {
    }

    virtual ~ViewPortBase();

    virtual void Init();
    virtual void RenderUI();
    void PreRenderViewPort();
    virtual void RenderViewPort();

    virtual void Tick(float deltaTime) = 0;
    virtual bool ScreenToTexture(const float x, const float y, float& outX, float& outY) = 0;

    bool IsWindowHovered();
    
    const char* GetGuiName();

    ImVec2 GetViewPortPos();

    ImVec2 GetViewPortSize();

    
private:
    const char* guiName;
    ImVec2 lastSize = ImVec2(0,0);
    ImVec2 viewPortPos = ImVec2(0,0);
    unsigned int viewPortTexture = 0;
    unsigned int FBO = 0;
    
    bool isWindowHovered = false;
};
