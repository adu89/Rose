#include "Graphics.h"

#include "Rose/Renderer/Renderer.h"
#include "Rose/Renderer/VertexArray.h"
#include "Rose/Renderer/Buffer.h"

#include <memory>

namespace Rose {
    std::string Graphics::vertexSrc(R"(
        #version 330 core

        layout(location = 0) in vec3 position;
        layout(location = 1) in vec4 color;

        uniform mat4 u_ViewProjection;

        out vec3 v_position;
        out vec4 v_color;

        void main()
        {
            v_position = position;
            v_color = color;
            gl_Position = u_ViewProjection * vec4(position, 1.0);
        }
    )");

    std::string Graphics::fragmentSrc(R"(
        #version 330 core

        in vec4 v_color;
        out vec4 color;

        void main()
        {
            color = v_color / 255;
        }
    )"); 

    void Graphics::DrawRectangle(float x, float y, float w, float h, float r, float g, float b, float a) 
    {
        float z = 0.0f;

        float vertices[4 * 7] = {
             x    , y + h, z, r, g, b, a,
             x + w, y + h, z, r, g, b, a,
             x + w, y    , z, r, g, b, a,        
             x    , y    , z, r, g, b, a        
        };

        std::shared_ptr<VertexArray> va;
        va.reset(VertexArray::Create());

        std::shared_ptr<VertexBuffer> vb;
        vb.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

        BufferLayout layout = {
            { ShaderDataType::Float3, "position" },
            { ShaderDataType::Float4, "color" }
        };

        vb->SetLayout(layout);        
        va->AddVertexBuffer(vb);        

        unsigned int indices[2 * 3] = {
            0, 1, 2,
            2, 3, 0
        };

        std::shared_ptr<IndexBuffer> ib;
        ib.reset(IndexBuffer::Create(indices, 2 * 3));

        va->SetIndexBuffer(ib);

        std::shared_ptr<Shader> s;
        s.reset(new Shader(Graphics::vertexSrc, Graphics::fragmentSrc));

        Rose::Renderer::Submit(s, va);   
    }
    
    void Graphics::DrawRectangle(const Rectangle& r, const Color& c) 
    {
        DrawRectangle(r.GetX(), r.GetY(), r.GetWidth(), r.GetHeight(), c.GetR(), c.GetG(), c.GetB(), c.GetAlpha());
    }
}