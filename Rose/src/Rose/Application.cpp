#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Log.h"
namespace Rose
{
    Application::Application()
    {
        window = std::unique_ptr<Window>(Window::Create());  
    }

    Application::~Application()
    {
    }    

    void Application::Run()
    {
        while(running)
        {
            window->OnUpdate();
        }
    }
} 
