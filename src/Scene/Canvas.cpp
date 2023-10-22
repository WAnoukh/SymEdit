#include "Canvas.h"

const unsigned Canvas::GetWidth() const
{
    return Width;
}

const unsigned Canvas::GetHeight() const
{
    return Height;
}

void Canvas::SetWidth(const unsigned int InWidth)
{
    Width =InWidth;
}

void Canvas::SetHeight(const unsigned int InHeight)
{
    Height = InHeight;
}
