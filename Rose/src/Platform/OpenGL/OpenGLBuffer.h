#pragma once

#include "Rose/Renderer/Buffer.h"

namespace Rose {
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        virtual ~OpenGLVertexBuffer();

        virtual void Bind() const override;
        virtual void UnBind() const override;

        virtual void SetLayout(const BufferLayout& bufferLayout) override { layout = bufferLayout; }
        virtual const BufferLayout& GetLayout() const override { return layout; }
    private:
        uint32_t rendererId;
        BufferLayout layout;
    };
    
    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(uint32_t* indices , uint32_t count);
        virtual ~OpenGLIndexBuffer();

        virtual void Bind() const override;
        virtual void UnBind() const override;

        uint32_t GetCount() const override { return count; }
    private:
        uint32_t rendererId;
        uint32_t count;
    };
} 