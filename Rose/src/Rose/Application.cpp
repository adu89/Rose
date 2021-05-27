#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Log.h"

#include <glad/glad.h>


namespace Rose
{
    Application* Application::instance = nullptr;

    Application::Application()
    {
        ROSE_CORE_ASSERT(!instance, "Application already exists!");
        instance = this;

        window = std::unique_ptr<Window>(Window::Create());  
        window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

        glGenVertexArrays(1, &vertexArray);
        glBindVertexArray(vertexArray);

        float vertices[3 * 3] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f        
        };

        vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
        
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

        unsigned int indices[3] = {
            0, 1, 2
        };

        indexBuffer.reset(IndexBuffer::Create(indices, 3));

        std::string vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 position;

            out vec3 v_position;

            void main()
            {
                v_position = position;
                gl_Position = vec4(position, 1.0);
            }
        )";

        std::string fragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec3 v_position;

            void main()
            {
                color = vec4(v_position * 0.5 + 0.5, 1.0);
            }
        )";        

        shader.reset(new Shader(vertexSrc, fragmentSrc));
    }

    Application::~Application()
    {
    }    

    void Application::PushLayer(Layer* layer)
    {
        layerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* layer)
    {
        layerStack.PushLayer(layer);
        layer->OnAttach();
    }   

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

        ROSE_CORE_TRACE("{0}", e);

        for(auto it = layerStack.end(); it != layerStack.begin(); )
        {
            (*--it)->OnEvent(e);
            if(e.Handled)
                break;
        }
    }

    void Application::Run()
    {
        while(running)
        {
            glClearColor(0.1f, 0.1f, 0.1f, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            shader->Bind();
            glBindVertexArray(vertexArray);
            glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

            for(Layer* layer : layerStack)
                layer->OnUpdate();
                
            window->OnUpdate();
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& event)
    {
        running = false;
        return true;
    }
} 
