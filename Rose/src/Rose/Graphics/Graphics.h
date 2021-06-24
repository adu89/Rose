#pragma once

#include <string>

#include "Rose/Geometry/Rectangle.h"
#include "Color.h"
#include "Rose/Renderer/Shader.h"
#include "Font.h"

namespace Rose {
    class Graphics
    {
    public:
        static void DrawRectangle(float x, float y, float w, float h, float r, float g, float b, float a);
        static void DrawRectangle(const Rectangle& rectangle, const Color& c);
        static void DrawText(float x, float y, float scale, const std::string& text, const Font& font);
    private: 
        static std::string vertexSrc;
        static std::string fragmentSrc;

        static std::string textVertexSrc;
        static std::string textFragmentSrc;
    };
}