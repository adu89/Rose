#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Rose {
    VertexArray* VertexArray::Create() 
    {
        switch(Renderer::GetAPI())
        {
            case RendererAPI::API::None:
                ROSE_CORE_ASSERT(false, "Renderer api none is not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return new OpenGLVertexArray();
        }

        ROSE_CORE_ASSERT(false, "Unknown renderer api!");
        return nullptr;       
    }
}