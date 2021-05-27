#pragma once

#include <string>

namespace Rose {
    class Shader 
    {
    public:
        Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~Shader();

        void Bind();
        void UnBind();
    private:
        uint32_t rendererId;
    };
}