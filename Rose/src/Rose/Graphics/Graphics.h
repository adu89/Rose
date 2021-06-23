#pragma once

#include <string>

#include "Rose/Geometry/Rectangle.h"
#include "Color.h"
#include "Rose/Renderer/Shader.h"

namespace Rose {
    class Graphics
    {
    public:
        static void DrawRectangle(float x, float y, float w, float h, float r, float g, float b, float a);
        static void DrawRectangle(const Rectangle& r, const Color& c);
    private: 
        static std::string vertexSrc;
        static std::string fragmentSrc;
    };
}