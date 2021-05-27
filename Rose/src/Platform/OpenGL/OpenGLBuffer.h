#pragma once

#include "Rose/Renderer/Buffer.h"

namespace Rose {
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        virtual ~OpenGLVertexBuffer();

        void Bind() const override;
        void UnBind() const override;
    private:
        uint32_t rendererId;
    };
    
    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(uint32_t* indices , uint32_t count);
        virtual ~OpenGLIndexBuffer();

        void Bind() const override;
        void UnBind() const override;

        uint32_t GetCount() const override { return count; }
    private:
        uint32_t rendererId;
        uint32_t count;
    };
} 