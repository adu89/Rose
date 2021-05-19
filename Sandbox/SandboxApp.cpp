#include <Rose.h>

class ExampleLayer : public Rose::Layer
{
public:
    ExampleLayer()
        : Layer("Example")
    { 
    }

    void OnUpdate() override
    {
        ROSE_INFO("ExampleLayer::Update");
    }

    void OnEvent(Rose::Event& event) override
    {
        // ROSE_TRACE("{0}", event);
    }
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