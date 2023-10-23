#include "Pen.h"

#include <algorithm>

#include "..\..\..\Scene\Viewport\TextureEditor.h"

void Pen::Apply(Texture& texture, TextureEditor& viewPort, float mouseX, float mouseY)
{
    float pixelX, pixelY;
    int pixelXInt, pixelYInt;
    viewPort.ScreenToTexture(mouseX, mouseY, pixelX, pixelY);
    if (true)
    {
        pixelX *= texture.GetWidth();
        pixelY *= texture.GetHeight();
        pixelXInt = static_cast<int>(pixelX);
        pixelYInt = static_cast<int>(pixelY);
        if(interpolate && !ignoreNextInterpolate)
        {
            if(pixelXInt == lastPixelX)
            {
                for (int y = std::min(pixelYInt, lastPixelY); y <= std::max(pixelYInt, lastPixelY); y++)
                {
                    Draw(pixelXInt,y,texture);
                }
            }else
            {
                int minX,maxX,minY,maxY;
                if(pixelXInt < lastPixelX)
                {
                    minX = pixelXInt;
                    maxX = lastPixelX;
                    minY = pixelYInt;
                    maxY = lastPixelY;
                }
                else
                {
                    minX = lastPixelX;
                    maxX = pixelXInt;
                    minY = lastPixelY;
                    maxY = pixelYInt;
                }
            
                float a = static_cast<float>(maxY - minY) / static_cast<float>(maxX - minX);
                int lastDrawedY = minY;
                for(int x = minX; x <= maxX; x++)
                {
                    int newY = (x - minX) * a + minY;
                    for (int y = std::min(newY, lastDrawedY)+1; y < std::max(newY, lastDrawedY); y++)
                    {
                        Draw(x,y,texture);
                    }
                    Draw(x,newY,texture);
                    lastDrawedY = newY;
                }
            }
        }else
        {
            ignoreNextInterpolate = false;
        }
        
        texture.EditPixel(pixelXInt, pixelYInt, color, 255);
        texture.SendDataToOpenGl();
        lastPixelX = pixelXInt;
        lastPixelY = pixelYInt;
    }else
    {
        ignoreNextInterpolate = true;
    }

}

void Pen::RenderUI()
{
    ImGui::Begin("Pen");
    ImGui::SliderFloat3("Color", uiColor, 0.0f, 255.0f);
    color[0] = static_cast<unsigned char>(uiColor[0]);
    color[1] = static_cast<unsigned char>(uiColor[1]);
    color[2] = static_cast<unsigned char>(uiColor[2]);
    ImGui::SliderInt("Size", &size, 1, 100);
    ImGui::End();
}

void Pen::SetInterpolate(bool inInterpolate)
{
    interpolate = inInterpolate;
}

void Pen::Draw(int x, int y, Texture& texture)
{
    for(int i = -size; i < size; i++)
    {
        for(int j = -size; j < size; j++)
        {
            if(i*i + j*j < size*size)
            {
                texture.EditPixel(x+i, y+j, color, 255);
            }
        }
    }
    
}
