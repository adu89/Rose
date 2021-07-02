#include "Graphics.h"

#include "Rose/Renderer/Renderer.h"
#include "Rose/Renderer/VertexArray.h"
#include "Rose/Renderer/Buffer.h"

#include <memory>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Rose/Application.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Rose {
    std::string Graphics::textVertexSrc(R"(
        #version 330 core

        layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
        out vec2 TexCoords;

        uniform mat4 u_ViewProjection;

        void main()
        {
            gl_Position = u_ViewProjection * vec4(vertex.xy, 0.0, 1.0);
            TexCoords = vertex.zw;
        }          
    )");

    std::string Graphics::textFragmentSrc(R"(
        #version 330 core

        in vec2 TexCoords;
        out vec4 color;

        uniform sampler2D text;
        uniform vec3 textColor;

        void main()
        {    
            vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
            color = vec4(0.5, 0.8f, 0.2f, 1.0) * sampled;
        }          
    )");

    std::string Graphics::vertexSrc(R"(
        #version 330 core

        layout(location = 0) in vec3 position;

        uniform mat4 u_ViewProjection;

        out vec3 v_position;

        void main()
        {
            v_position = position;
            gl_Position = u_ViewProjection * vec4(position, 1.0);
        }
    )");

    std::string Graphics::fragmentSrc(R"(
        #version 330 core

        in vec4 v_color;
        out vec4 color;

        uniform vec4 u_Color;

        void main()
        {
            color = u_Color / 255;
        }
    )"); 

    void Graphics::DrawRectangle(float x, float y, float w, float h, const Color& c) 
    {
        float z = 0.0f;

        float vertices[4 * 3] = {
             x    , y + h, z, 
             x + w, y + h, z, 
             x + w, y    , z,         
             x    , y    , z        
        };

        std::shared_ptr<VertexArray> va;
        va.reset(VertexArray::Create());

        std::shared_ptr<VertexBuffer> vb;
        vb.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

        BufferLayout layout = {
            { ShaderDataType::Float3, "position" }
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
        s.reset(Shader::Create(Graphics::vertexSrc, Graphics::fragmentSrc));

        s->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(s)->UploadUniformFloat4("u_Color", glm::vec4(c.GetR(), c.GetG(), c.GetB(), c.GetAlpha()));

        Rose::Renderer::Submit(s, va);   
    }
    
    void Graphics::DrawRectangle(const Rectangle& r, const Color& c) 
    {
        DrawRectangle(r.GetX(), r.GetY(), r.GetWidth(), r.GetHeight(), c);
    }
    
    void Graphics::DrawText(float x, float y, const std::string& text, const Font& font) 
    {
        // std::shared_ptr<VertexArray> va;
        // va.reset(VertexArray::Create());

        // std::shared_ptr<VertexBuffer> vb;
        // vb.reset(VertexBuffer::Create());

        auto* app = Application::Get();
        glm::mat4 camera(glm::ortho(0.0f, (float)app->GetWindow().GetWidth(), (float)app->GetWindow().GetHeight(), 0.0f, -1.0f, 1.0f));

        unsigned int VAO, VBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0); 
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);  

        std::shared_ptr<Shader> s;
        s.reset(Shader::Create(Graphics::textVertexSrc, Graphics::textFragmentSrc));

        s->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(s)->UploadUniforMat4("u_ViewProjection", camera);

        //glUniform3f(glGetUniformLocation(s., "textColor"), 1, 1, 1);
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(VAO);

        for(std::string::size_type i = 0; i < text.size(); ++i)
        {
            const std::map<char, Character>& characters = font.GetCharacters();
            const Character& c = characters.at(text[i]);

            float xpos = x + (i == 0 ? 0 : c.Bearing.x);
            //float ypos = (y + font.GetSize() - c.Bearing.y - font.GetMaxDescent()) * scale;
            float ypos = y - c.Bearing.y + font.GetMaxBearingY(text);

            float w = c.Size.x;
            float h = c.Size.y;

            // update VBO for each character
            // float vertices[6 * 4] = {
            //     xpos,     ypos + h,   0.0f, 0.0f,            
            //     xpos,     ypos,       0.0f, 1.0f,
            //     xpos + w, ypos,       1.0f, 1.0f,
            //     xpos,     ypos + h,   0.0f, 0.0f,
            //     xpos + w, ypos,       1.0f, 1.0f,
            //     xpos + w, ypos + h,   1.0f, 0.0f           
            // }; 

            float vertices[6 * 4] = {
                xpos,     ypos + h,   0.0f, 1.0f,
                xpos + w, ypos + h,   1.0f, 1.0f,
                xpos + w, ypos    ,   1.0f, 0.0f,           
                xpos + w, ypos    ,   1.0f, 0.0f,
                xpos,     ypos    ,   0.0f, 0.0f,        
                xpos,     ypos + h,   0.0f, 1.0f    
            };             

            glBindTexture(GL_TEXTURE_2D, c.TextureId);
            // update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
            // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            x += (c.Advance >> 6); // bitshift by 6 to get value in pixels (2^6 = 64)                       
        }
    }
    
    void Graphics::DrawText(const Rectangle& boundingRect, const std::string& text, const Font& font) 
    {
        float textHeight = font.GetMaxBearingY(text) + font.GetMinBearingY(text);
        float yOffset = (boundingRect.GetHeight() - textHeight) / 2.0f; 

        ROSE_CORE_ASSERT(yOffset >= 0, "Y offset cannot be less than 0");    
        
        float textWidth = font.GetStringWidth(text);
        float xOffset = (boundingRect.GetWidth() - textWidth) / 2.0f;    
        
        ROSE_CORE_ASSERT(xOffset >= 0, "X offset cannot be less than 0");    
        
        DrawText(boundingRect.GetX() + xOffset, boundingRect.GetY() + yOffset, text, font);
    }
} 