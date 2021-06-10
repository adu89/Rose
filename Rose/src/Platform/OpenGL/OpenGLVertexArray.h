#pragma once

#include "Rose/Renderer/VertexArray.h"

#include <vector>
#include <memory>

namespace Rose {
    class OpenGLVertexArray : public VertexArray
    {
    public:
       OpenGLVertexArray(); 
       virtual ~OpenGLVertexArray();

        void Bind() const override;
        void UnBind() const override;
        void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override; 
        void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;
        const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const { return vertexBuffers; }
        const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return indexBuffer; } 
    private:
        std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers;    
        std::shared_ptr<IndexBuffer> indexBuffer;    
        uint32_t rendererId;
    };
}
