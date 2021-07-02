#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Rose {
    Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc) 
    {
        switch(Renderer::GetAPI())
        {
            case RendererAPI::API::None:
                ROSE_CORE_ASSERT(false, "Renderer api none is not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return new OpenGLShader(vertexSrc, fragmentSrc);
        }

        ROSE_CORE_ASSERT(false, "Unknown renderer api!");
        return nullptr;       
    }
}