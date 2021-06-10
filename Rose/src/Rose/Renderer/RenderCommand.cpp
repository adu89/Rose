#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Rose {
    RendererAPI* RenderCommand::rendererAPI = new OpenGLRendererAPI;
}