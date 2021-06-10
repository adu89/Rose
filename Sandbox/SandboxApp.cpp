#include <Rose.h>

#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public Rose::Layer
{
public:
    ExampleLayer()
        : Layer("Example")
    { 
         vertexArray.reset(Rose::VertexArray::Create());

        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
             0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f        
        };

        vertexBuffer.reset(Rose::VertexBuffer::Create(vertices, sizeof(vertices)));
    
        Rose::BufferLayout layout = {
            { Rose::ShaderDataType::Float3, "position" },
            { Rose::ShaderDataType::Float4, "color" }
        };

        vertexBuffer->SetLayout(layout);        
        vertexArray->AddVertexBuffer(vertexBuffer);

        unsigned int indices[3] = {
            0, 1, 2
        };

        indexBuffer.reset(Rose::IndexBuffer::Create(indices, 3));
        vertexArray->SetIndexBuffer(indexBuffer);

        squareVertexArray.reset(Rose::VertexArray::Create());
        
        auto* app = Rose::Application::Get();

        float squareVertices[4 * 3] = {
             0.0f, (float)app->GetWindow().GetHeight(), 0.0f, 
            
             (float)app->GetWindow().GetWidth(), (float)app->GetWindow().GetHeight(), 0.0f, 
             (float)app->GetWindow().GetWidth(),  0.0f, 0.0f,         
            0.0f,  0.0f, 0.0f        
        };

        std::shared_ptr<Rose::VertexBuffer> squareVertexBuffer; 
        squareVertexBuffer.reset(Rose::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

        Rose::BufferLayout squarelayout = {
            { Rose::ShaderDataType::Float3, "position" }
        }; 

        squareVertexBuffer->SetLayout(squarelayout);

        squareVertexArray->AddVertexBuffer(squareVertexBuffer);

        unsigned int squareIndices[2 * 3] = {
            0, 1, 2,
            2, 3, 0
        };

        std::shared_ptr<Rose::IndexBuffer> squareIndexBuffer;
        squareIndexBuffer.reset(Rose::IndexBuffer::Create(squareIndices, 2 * 3));
        
        squareVertexArray->SetIndexBuffer(squareIndexBuffer);        

        std::string vertexSrc = R"(
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
        )";

        std::string fragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec3 v_position;
            in vec4 v_color;

            void main()
            {
                color = vec4(v_position * 0.5 + 0.5, 1.0);
                color = v_color;
            }
        )";        

        shader.reset(new Rose::Shader(vertexSrc, fragmentSrc));

        std::string vertexSrc2 = R"(
            #version 330 core

            layout(location = 0) in vec3 position;

            uniform mat4 u_ViewProjection;

            out vec3 v_position;

            void main()
            {
                v_position = position;
                gl_Position = u_ViewProjection * vec4(position, 1.0);
            }
        )";

        std::string fragmentSrc2 = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec3 v_position;

            void main()
            {
                color = vec4(0.2, 0.3, 0.8, 1);
            }
        )";   

        shader2.reset(new Rose::Shader(vertexSrc2, fragmentSrc2));
    }

    void OnUpdate(Rose::Timestep ts) override
    {
        Rose::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        Rose::RenderCommand::Clear();

        auto* app = Rose::Application::Get();

        glm::mat4 camera(glm::ortho(0.0f, (float)app->GetWindow().GetWidth(), 0.0f, (float)app->GetWindow().GetHeight(), -1.0f, 1.0f));

        Rose::Renderer::BeginScene(camera);

        Rose::Renderer::Submit(shader2, squareVertexArray);
            
        Rose::Renderer::Submit(shader, vertexArray);
            
        Rose::Renderer::EndScene();        
    }

    void OnEvent(Rose::Event& event) override
    {
        // ROSE_TRACE("{0}", event);
    }

    private:
        std::shared_ptr<Rose::Shader> shader;
        std::shared_ptr<Rose::VertexBuffer> vertexBuffer;
        std::shared_ptr<Rose::IndexBuffer> indexBuffer;
        std::shared_ptr<Rose::VertexArray> vertexArray;

        std::shared_ptr<Rose::VertexArray> squareVertexArray;
        std::shared_ptr<Rose::Shader> shader2;
};
class SandboxApp : public Rose::Application
{
public:
    SandboxApp()
    {
        PushLayer(new ExampleLayer()); 
    }

    ~SandboxApp()
    {
    }
};

Rose::Application* Rose::CreateApplication()
{
    return new SandboxApp();
}