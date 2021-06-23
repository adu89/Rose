#pragma once

#include "Rose/Renderer/VertexArray.h"

#include <memory>

namespace Rose {
    class Rectangle
    {
    public:
        Rectangle(float x, float y, float width, float height)
            : x(x), y(y), width(width), height(height)
        {
        }

        ~Rectangle() {};

        bool Contains(int mouseX, int mouseY) const
        {
            if(mouseX >= x && mouseX <= (x + width) &&
                mouseY >= y && mouseY <= (y + height))
                return true;
        
            return false;
        }

        float GetX() const { return x; };
        float GetY() const { return y; };
        float GetWidth() const { return width; };
        float GetHeight() const { return height; };

    private:
        float x;
        float y;
        float width;
        float height;
    };
}