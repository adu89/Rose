#include "Buffer.h"

#include "Rose/Log.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Rose {
    VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) 
    {
        switch(Renderer::GetAPI())
        {
            case RendererAPI::API::None:
                ROSE_CORE_ASSERT(false, "Renderer api none is not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return new OpenGLVertexBuffer(vertices, size);
        }

        ROSE_CORE_ASSERT(false, "Unknown renderer api!");
        return nullptr;
    }
    
    IndexBuffer* IndexBuffer::Create(uint32_t* indices , uint32_t count) 
    {
        switch(Renderer::GetAPI())
        {
            case RendererAPI::API::None:
                ROSE_CORE_ASSERT(false, "Renderer api none is not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return new OpenGLIndexBuffer(indices, count);
        }

        ROSE_CORE_ASSERT(false, "Unknown renderer api!");
        return nullptr;        
    }
}