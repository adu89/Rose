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

        inline static Application* Get() { return instance; }
        inline Window& GetWindow() { return *window; }
    private:
        bool OnWindowClose(WindowCloseEvent& event);

        std::unique_ptr<Window> window;
        bool running = true;

        LayerStack layerStack;
    private:
        static Application* instance;
    };

    Application* CreateApplication();
}