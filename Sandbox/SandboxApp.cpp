#include <Rose.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

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