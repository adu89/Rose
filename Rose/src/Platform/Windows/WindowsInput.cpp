#include "Rose/Input.h"
#include "Rose/Application.h"

#include <GLFW/glfw3.h>

namespace Rose
{
    bool Input::IsKeyPressed(int keycode)
    {
        auto window = static_cast<GLFWwindow*>(Application::Get()->GetWindow().GetNativeWindow());
        auto state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT; 
    }

    bool Input::IsMouseButtonPressed(int button)
    {
        auto window = static_cast<GLFWwindow*>(Application::Get()->GetWindow().GetNativeWindow());
        auto state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS; 
    }

    MousePosition Input::GetMousePosition() 
    {
        auto window = static_cast<GLFWwindow*>(Application::Get()->GetWindow().GetNativeWindow());
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);
        return MousePosition((float)xPos, (float)yPos);
    }

    float Input::GetMouseX()
    {
        auto[x, y] = GetMousePosition();
        return x;   
    }

    float Input::GetMouseY()
    {
        auto[x, y] = GetMousePosition();
        return y;  
    }

    std::pair<int, int> Input::GetWindowSize()
    {
        auto window = static_cast<GLFWwindow*>(Application::Get()->GetWindow().GetNativeWindow());
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        return { width, height };
    }
}