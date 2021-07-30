#include "OpenGLTexture.h"

#include <glad/glad.h>

namespace Rose
{
    OpenGLTexture2D::OpenGLTexture2D(const std::string& path) 
        : path(path)
    {
        
    }
    
    OpenGLTexture2D::OpenGLTexture2D(unsigned char* buffer, uint32_t width, uint32_t height) 
        : width(width), height(height)
    {
        glCreateTextures(GL_TEXTURE_2D, 1, &rendererId);
        glTextureStorage2D(rendererId, 0, GL_RED, width, height);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTextureSubImage2D(rendererId, 0, 0, 0, width, height, GL_RED, GL_UNSIGNED_BYTE, buffer);
    }
    
    OpenGLTexture2D::~OpenGLTexture2D() 
    {
        glDeleteTextures(1, &rendererId);
    }
    
    void OpenGLTexture2D::Bind(uint32_t slot) const 
    {
        glBindTextureUnit(slot, rendererId);
    }
}