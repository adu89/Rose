#pragma once

#include "Rose/Log.h"

#include <cstdint>
#include <vector>
#include <string>
namespace Rose {
    enum class ShaderDataType 
    {
        None = 0,
        Float,
        Float2,
        Float3,
        Float4,
        Mat3,
        Mat4,
        Int,
        Int2,
        Int3,
        Int4,
        Bool
    };

    static uint32_t ShaderDataTypeSize(ShaderDataType type)
    {
        switch(type)
        {
            case ShaderDataType::Float:  return 4;
            case ShaderDataType::Float2: return 4 * 2;
            case ShaderDataType::Float3: return 4 * 3;
            case ShaderDataType::Float4: return 4 * 4;
            case ShaderDataType::Mat3:   return 4 * 3 * 3;
            case ShaderDataType::Mat4:   return 4 * 4 * 4;
            case ShaderDataType::Int:    return 4;
            case ShaderDataType::Int2:   return 4 * 2;
            case ShaderDataType::Int3:   return 4 * 3;
            case ShaderDataType::Int4:   return 4 * 4;
            case ShaderDataType::Bool:   return 1;
        }

        ROSE_CORE_ASSERT(false, "Unknown shader data type!")
        return 0;
    }
    struct BufferElement
    {
        std::string Name;
        ShaderDataType Type;        
        uint32_t Size;
        uint32_t Offset;
        bool Normalized;

        BufferElement() {}

        BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
            : Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
        {
        }

        uint32_t GetComponentCount() const
        { 
            switch(Type)
            {
                case ShaderDataType::Float:  return 1;
                case ShaderDataType::Float2: return 2;
                case ShaderDataType::Float3: return 3;
                case ShaderDataType::Float4: return 4;
                case ShaderDataType::Mat3:   return 3 * 3;
                case ShaderDataType::Mat4:   return 4 * 4;
                case ShaderDataType::Int:    return 1;
                case ShaderDataType::Int2:   return 2;
                case ShaderDataType::Int3:   return 3;
                case ShaderDataType::Int4:   return 4;
                case ShaderDataType::Bool:   return 1;
            }

            ROSE_CORE_ASSERT(false, "Unknown shader data type!")
            return 0;
        }
    };
    class BufferLayout
    {
    public:
        BufferLayout() {}
        BufferLayout(const std::initializer_list<BufferElement>& elements)
            : elements(elements)
        {
            CalculateOffsetAndStride();
        }

        inline const std::vector<BufferElement>& GetElements() const { return elements; }
        inline const uint32_t GetStride() const { return stride; }

        std::vector<BufferElement>::iterator begin() { return elements.begin(); }
        std::vector<BufferElement>::iterator end() { return elements.end(); }
        std::vector<BufferElement>::const_iterator begin() const { return elements.begin(); }
        std::vector<BufferElement>::const_iterator end() const { return elements.end(); }

    private:
        void CalculateOffsetAndStride()
        {
            uint32_t offset = 0;
            stride = 0;
            for(auto& element : elements)
            {
                element.Offset = offset;
                offset += element.Size;
                stride += element.Size;
            }
        }
    private:
        std::vector<BufferElement> elements;
        uint32_t stride = 0;
    };
    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() {};

        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;

        virtual void SetLayout(const BufferLayout& layout) = 0;
        virtual const BufferLayout& GetLayout() const = 0; 

        static VertexBuffer* Create(float* vertices, uint32_t size);
    };  
    
    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer() {};

        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;

        virtual uint32_t GetCount() const = 0;

        static IndexBuffer* Create(uint32_t* indices , uint32_t count);        
    };
}