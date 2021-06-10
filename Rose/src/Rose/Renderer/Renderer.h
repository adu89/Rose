#pragma once

#include "RenderCommand.h"
#include "Shader.h"
#include <glm/glm.hpp>

namespace Rose {
    class Renderer
    { 
    public:
        static void BeginScene(glm::mat4& camera);
        static void EndScene();
 
        static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray); 

        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
    private:
        static glm::mat4 camera;
    };
}