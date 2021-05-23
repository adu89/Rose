#include "WindowsInput.h"

#include "Rose/Application.h"

#include <GLFW/glfw3.h>

namespace Rose
{
     Input* Input::instance = new WindowsInput();

    bool WindowsInput::IsKeyPressedImpl(int keycode)
    {
        auto window = static_cast<GLFWwindow*>(Application::Get()->GetWindow().GetNativeWindow());
        auto state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT; 
    }

    bool IsMouseButtonPressedImpl(int button)
    {
        auto window = static_cast<GLFWwindow*>(Application::Get()->GetWindow().GetNativeWindow());
        auto state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS; 
    }

    std::pair<float, float> GetMousePositionImpl() 
    {
        auto window = static_cast<GLFWwindow*>(Application::Get()->GetWindow().GetNativeWindow());
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);
        return { (float)xPos, (float)yPos };
    }

    float GetMouseXImpl()
    {
        auto[x, y] = GetMousePositionImpl();
        return x;   
    }

    float GetMouseYImpl()
    {
        auto[x, y] = GetMousePositionImpl();
        return y;  
    }
}