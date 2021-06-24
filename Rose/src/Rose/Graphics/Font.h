#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H  

#include "Rose/Log.h"

#include <glm/glm.hpp>
#include <map>

namespace Rose {
    struct Character 
    {
        unsigned int TextureId;
        glm::ivec2 Size;
        glm::ivec2 Bearing;
        unsigned int Advance;
    };

    class Font
    {
    public:
        Font();
        ~Font();

        const std::map<char, Character>& GetCharacters() const;

    private:
        std::map<char, Character> characters;
    };
}