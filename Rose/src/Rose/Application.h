#pragma once

namespace Rose 
{
    class Application  
    {
    public:
        Application();
        virtual ~Application();
    public:
        void Run();
    };

    Application* CreateApplication();
}