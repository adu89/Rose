#pragma once

#include "Rose/Renderer/Texture.h"
#include <string>

namespace Rose {
    class OpenGLTexture2D : public Texture2D
    {
    public:
        OpenGLTexture2D(const std::string& path);
        OpenGLTexture2D(unsigned char* buffer, uint32_t width, uint32_t height);
        virtual ~OpenGLTexture2D();

        virtual uint32_t GetWidth() const override { return width; }
        virtual uint32_t GetHeight() const override { return height; }

        virtual void Bind(uint32_t slot = 0) const override; 

    private:
        uint32_t width;
        uint32_t height;
        uint32_t rendererId;
        std::string path;
    };
}