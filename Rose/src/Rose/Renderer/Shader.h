#pragma once

#include <string>

#include <glm/glm.hpp>

namespace Rose {
    class Shader 
    {
    public:
        Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~Shader();

        void Bind();
        void UnBind();

        void UploadUniforMat4(const std::string& name, const glm::mat4& matrix);
    private:
        uint32_t rendererId;
    };
}