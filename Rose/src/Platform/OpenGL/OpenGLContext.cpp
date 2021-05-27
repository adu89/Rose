#include "OpenGLContext.h"

#include "Rose/Log.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Rose {
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) 
        : windowHandle(windowHandle)
    {      
        ROSE_CORE_ASSERT(windowHandle, "Handle is null!");
    }
    
    void OpenGLContext::Init() 
    {
        glfwMakeContextCurrent(windowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        ROSE_CORE_ASSERT(status, "Failed to initialise glad!");

        ROSE_CORE_INFO("OpenGL Info:");
        ROSE_CORE_INFO("    Vendor: {0}", glGetString(GL_VENDOR));
        ROSE_CORE_INFO("    Renderer: {0}", glGetString(GL_RENDERER));
        ROSE_CORE_INFO("    Version: {0}", glGetString(GL_VERSION));
    }
    
    void OpenGLContext::SwapBuffers() 
    {
        glfwSwapBuffers(windowHandle);
    }
}