#include "WindowsWindow.h"

#include "Rose/Core.h"
#include "Rose/Log.h"
#include "Rose/Events/ApplicationEvent.h"
#include "Rose/Events/KeyEvent.h"
#include "Rose/Events/MouseEvent.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Rose
{
    static bool GLFWInitialised = false;

    static void GLFWErrorCallback(int error, const char* description)
    {
        ROSE_CORE_ASSERT("GLFW Error ({0}): {1} ", error, description);
    }

    Window* Window::Create(const WindowProps& props)
    {
        return new WindowsWindow(props);
    }

    WindowsWindow::WindowsWindow(const WindowProps& props)
    {
        Init(props);
    }

    WindowsWindow::~WindowsWindow()
    {
    }

    void WindowsWindow::Init(const WindowProps& props)
    {
        data.Title = props.Title;
        data.Width = props.Width;
        data.Height = props.Height;

        ROSE_CORE_INFO("Creating window {0}, ({1}, {2})", props.Title, props.Width, props.Height);
        
        if(!GLFWInitialised)
        {
            int success = glfwInit();
            ROSE_CORE_ASSERT(success, "Could not initialise GLFW!");

            glfwSetErrorCallback(GLFWErrorCallback);

            GLFWInitialised = true;
        }

        window = glfwCreateWindow((int)props.Width, (int)props.Height, data.Title.c_str(), nullptr, nullptr);
        
        context = new OpenGLContext(window); 
        context->Init();

        glfwSetWindowUserPointer(window, &data);
        SetVSync(true);

        glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) 
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            WindowResizeEvent event(width, height);
            data.Width = width;
            data.Height = height;
            data.EventCallback(event);
        });

        glfwSetWindowCloseCallback(window, [](GLFWwindow* window) 
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            WindowCloseEvent event;
            data.EventCallback(event);
        });
        
        glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) 
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch(action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, 0);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, 1);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch(action)
            {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    data.EventCallback(event);
                    break;
                } 
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset) 
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            data.EventCallback(event);
        });

        glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y) 
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float)x, (   float)y);
            data.EventCallback(event);
        });
    }

    void WindowsWindow::Shutdown()
    {
        glfwDestroyWindow(window);
    }

    void WindowsWindow::OnUpdate()
    {
        glfwPollEvents();
        context->SwapBuffers();
    }

    void WindowsWindow::SetVSync(bool enabled)
    {
        if(enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);
        
        data.VSync = enabled;
    }
    
    bool WindowsWindow::IsVSync() const
    {
        return data.VSync;
    }
}