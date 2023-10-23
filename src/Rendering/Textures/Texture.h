#pragma once

#include <glad/glad.h>

class Texture
{
public:
    void CreateBlankTexture(int inWidth, int inHeight, GLenum inFormat);

    bool EditPixel(int inX, int inY, unsigned char color[3], unsigned char alpha = 255);

    void GenerateOpenGlTexture();
    void SendDataToOpenGl();
    unsigned int GetTextureId() const;

    int GetWidth() const { return width; }
    int GetHeight() const { return height; }
    
private:
    unsigned char* data = nullptr;
    int width;
    int height;
    unsigned int textureID;
    GLenum format;
};
