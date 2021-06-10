#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Log.h"
#include "Renderer/Renderer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

namespace Rose
{
    Application* Application::instance = nullptr;

    Application::Application()
    {
        ROSE_CORE_ASSERT(!instance, "Application already exists!");
        instance = this;

        window = std::unique_ptr<Window>(Window::Create());  
        window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
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
            float time = (float)glfwGetTime();
            Timestep timestep = time - lastFrameTime;  
            lastFrameTime = time;

            for(Layer* layer : layerStack)
                layer->OnUpdate(timestep);
                
            window->OnUpdate();
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& event)
    {
        running = false;
        return true;
    }
} 
