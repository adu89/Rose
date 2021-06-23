#include <Rose.h>

#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public Rose::Layer
{
public:
    ExampleLayer()
        : Layer("Example")
    { 
    }

    void OnUpdate(Rose::Timestep ts) override
    {
        Rose::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        Rose::RenderCommand::Clear();

        auto* app = Rose::Application::Get();
        glm::mat4 camera(glm::ortho(0.0f, (float)app->GetWindow().GetWidth(), (float)app->GetWindow().GetHeight(), 0.0f, -1.0f, 1.0f));
        
        Rose::Renderer::BeginScene(camera);

        uiState.MousePosition = Rose::Input::GetMousePosition();
        uiState.IsMouseDown = Rose::Input::IsMouseButtonPressed(0);
        uiState.HotItem = 0;

        if(uiState.IsMouseDown)
            ROSE_ERROR("MOUSE_BUTTON_PRESSED");

        Rose::Rectangle rectangle(100, 100, 100, 100);

        if(Rose::Widgets::Button(1, rectangle, uiState))
            ROSE_INFO("Button clicked");

        Rose::Rectangle rectangle2(rectangle.GetRight(), rectangle.GetY(), 100, 100);

        if(Rose::Widgets::Button(2, rectangle2, uiState))
            ROSE_INFO("Button clicked");
            
        if(!uiState.IsMouseDown)
        {
            uiState.ActiveItem = 0;
        }
        else
        {
            if(uiState.ActiveItem == 0)
                uiState.ActiveItem = -1;
        }


        Rose::Renderer::EndScene();        
    }

    void OnEvent(Rose::Event& event) override
    {
        // ROSE_TRACE("{0}", event);
    }

    private:
        Rose::UIState uiState;
        
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