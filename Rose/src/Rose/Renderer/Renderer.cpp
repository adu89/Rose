#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Rose {
    glm::mat4 Renderer::camera = glm::mat4();

    void Renderer::BeginScene(glm::mat4& cam) 
    {
        camera = cam;
    }
    
    void Renderer::EndScene() 
    {
        
    }
    
    void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray) 
    {
        shader->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniforMat4("u_ViewProjection", camera);
        vertexArray->Bind(); 
        RenderCommand::DrawIndexed(vertexArray);
    }
}