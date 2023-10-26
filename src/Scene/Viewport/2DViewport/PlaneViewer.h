#pragma once
#include "ViewPort2D.h"

class Shader;

class PlaneViewer : public ViewPort2D
{
public:
    PlaneViewer() : ViewPort2D("PlaneViewer") {}
    ~PlaneViewer() override;
    
    void Init() override;
    void RenderViewPort() override;
    void RenderUI() override;

    void Tick(float deltaTime) override;

    bool ScreenToTexture(const float x, const float y, float& outX, float& outY) override;

private:
    unsigned int VBO = 0;
    unsigned int EBO = 0;
    unsigned int VAO = 0;
    Shader* shader;   

};
