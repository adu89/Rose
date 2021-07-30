#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H  

#include "Rose/Log.h"

#include <glm/glm.hpp>
#include <string>
#include <map>

namespace Rose {
    struct Character 
    {
        unsigned int TextureId;
        glm::ivec2 Size;
        glm::ivec2 Bearing;
        unsigned int Advance;
        float Descent;
        float Width;
    };

    class Font
    {
    public:
        enum Justification
        {
            Centered
        };

        Font(int size);
        ~Font();

        const std::map<char, Character>& GetCharacters() const;
        const float GetSize() const;
        const float GetMaxBearingY(const std::string& str) const;
        const float GetMinBearingY(const std::string& str) const;
        const float GetStringWidth(const std::string& str) const;

    private:
        float size;
        std::map<char, Character> characters;
    };
}