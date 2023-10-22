#pragma once

class Canvas
{
public:
    const unsigned int GetWidth() const;
    const unsigned int GetHeight() const;
    
    void SetWidth(const unsigned int InWidth);
    void SetHeight(const unsigned int InHeight);
    
private:
    unsigned int Width = 200;
    unsigned int Height = 200;
};
