#include "Pen.h"
#include "../../../Scene/ViewPort.h"

void Pen::Apply(Texture& texture, ViewPort& viewPort, float mouseX, float mouseY)
{
    float pixelX, pixelY;
    if (viewPort.ScreenToTexture(mouseX, mouseY, pixelX, pixelY))
    {
        pixelX *= texture.GetWidth();
        pixelY *= texture.GetHeight();
        texture.EditPixel(static_cast<int>(pixelX), static_cast<int>(pixelY), color, 255);
        texture.SendDataToOpenGl();
    }
}
