#pragma once

#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"

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
        void OnEvent(Event& e);
        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);
    private:
        bool OnWindowClose(WindowCloseEvent& event);

        std::unique_ptr<Window> window;
        bool running = true;

        LayerStack layerStack;
    };

    Application* CreateApplication();
}