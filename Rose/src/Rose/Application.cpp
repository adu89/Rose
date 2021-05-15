#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Log.h"
namespace Rose
{
    Application::Application()
    {
    }

    Application::~Application()
    {
    }    

    void Application::Run()
    {
        WindowResizeEvent e(1280, 720);
        ROSE_TRACE(e);

        while(true);
    }
} 
