#pragma once

#include "Window.h"

#include <memory>

namespace Rose 
{
    class Application  
    {
    public:
        Application();
        virtual ~Application();
    public:
        void Run();
    private:
        std::unique_ptr<Window> window;
        bool running = true;
    };

    Application* CreateApplication();
}