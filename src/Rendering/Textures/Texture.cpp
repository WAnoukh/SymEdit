#include "Texture.h"

#include <iostream>

void Texture::CreateBlankTexture(int inWidth, int inHeight, GLenum inFormat)
{
    if(inFormat != GL_RGB && inFormat != GL_RGBA)
    {
        std::cout << "Texture format not supported" << std::endl;
        return;
    }

    int dataSize = inWidth * inHeight * (inFormat == GL_RGB ? 3 : 4);

    data = new unsigned char[dataSize];

    for (int i = 0; i < dataSize; i++)
    {
        data[i] = 255;
    }
    format = inFormat;
    width = inWidth;
    height = inHeight;

    unsigned char color[3]  = {255,0,0};
}

void Texture::EditPixel(int inX, int inY, unsigned char color[3], unsigned char alpha)
{
    if (inX < 0 || inX >= width || inY < 0 || inY >= height)
    {
        std::cerr << "Pixel out of bounds" << std::endl;
        return;
    }
    unsigned int pixelSize = format == GL_RGB ? 3 : 4;
    data[(inX + inY * width) * (pixelSize)] = color[0];
    data[(inX + inY * width) * (pixelSize) + 1] = color[1];
    data[(inX + inY * width) * (pixelSize) + 2] = color[2];
    if (format == GL_RGBA)
    {
        data[(inX + inY * width) * (pixelSize) + 3] = alpha;
    }
}

void Texture::GenerateOpenGlTexture()
{
    glGenTextures(1, &textureID);
}

void Texture::SendDataToOpenGl()
{
    glBindTexture(GL_TEXTURE_2D, textureID);
    //To change if we want to load from texture file
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

unsigned Texture::GetTextureId() const
{
    return textureID; 
}
