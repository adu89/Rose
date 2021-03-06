#include "OpenGLVertexArray.h"

#include "Rose/Log.h"

#include <glad/glad.h>

namespace Rose {
    static GLenum ShaderDataTypeToOpenGLDataType(ShaderDataType type)
    {
        switch(type)
        {
            case ShaderDataType::Float:  return GL_FLOAT;
            case ShaderDataType::Float2: return GL_FLOAT;
            case ShaderDataType::Float3: return GL_FLOAT;
            case ShaderDataType::Float4: return GL_FLOAT;
            case ShaderDataType::Mat3:   return GL_FLOAT;
            case ShaderDataType::Mat4:   return GL_FLOAT;
            case ShaderDataType::Int:    return GL_INT;
            case ShaderDataType::Int2:   return GL_INT;
            case ShaderDataType::Int3:   return GL_INT;
            case ShaderDataType::Int4:   return GL_INT; 
            case ShaderDataType::Bool:   return GL_BOOL;
        }        
        
        ROSE_CORE_ASSERT(false, "Unknown shader data type!")
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray() 
    {
        glCreateVertexArrays(1, &rendererId);
    }
    
    OpenGLVertexArray::~OpenGLVertexArray() 
    {
        glDeleteVertexArrays(1, &rendererId);   
    }

    void OpenGLVertexArray::Bind() const 
    {
        glBindVertexArray(rendererId);
    }
    
    void OpenGLVertexArray::UnBind() const 
    {
        glBindVertexArray(0);
    }
    
    void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) 
    {
        ROSE_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layout!");

        glBindVertexArray(rendererId);
        vertexBuffer->Bind();

        uint32_t index = 0;
        for(const auto& element : vertexBuffer->GetLayout())
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, element.GetComponentCount(), 
                ShaderDataTypeToOpenGLDataType(element.Type), 
                element.Normalized ? GL_TRUE : GL_FALSE, 
                vertexBuffer->GetLayout().GetStride(), 
                (const void*)element.Offset);

            index++;
        }

        vertexBuffers.push_back(vertexBuffer);
    }
    
    void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& idxBuffer) 
    {
        glBindVertexArray(rendererId);
        idxBuffer->Bind();  

        indexBuffer = idxBuffer;
    } 
}