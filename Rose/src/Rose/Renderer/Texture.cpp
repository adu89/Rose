#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"
#include "Rose/Log.h"

namespace Rose {
    std::shared_ptr<Texture2D> Texture2D::Create(const std::string& path) 
    {
         switch(Renderer::GetAPI())
        {
            case RendererAPI::API::None:
                ROSE_CORE_ASSERT(false, "Renderer api none is not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return std::make_shared<OpenGLTexture2D>(path);
        }

        ROSE_CORE_ASSERT(false, "Unknown renderer api!");
        return nullptr;                
    }

    std::shared_ptr<Texture2D> Texture2D::Create(unsigned char* buffer, uint32_t width, uint32_t height) 
    {
         switch(Renderer::GetAPI())
        {
            case RendererAPI::API::None:
                ROSE_CORE_ASSERT(false, "Renderer api none is not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return std::make_shared<OpenGLTexture2D>(buffer, width, height);
        }

        ROSE_CORE_ASSERT(false, "Unknown renderer api!");
        return nullptr;                
    }
}