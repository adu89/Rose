#include "Font.h"

#include <glad/glad.h>
#include "Rose/Log.h"

#include <cmath>

namespace Rose {
    Font::Font(int size)
        : size(size)
    {
        FT_Library ft;
        if(FT_Init_FreeType(&ft)) {
            ROSE_CORE_ASSERT(false, "Could not initialise FreeType library.");
        }
        
        FT_Face face;
        if (FT_New_Face(ft, "ARB 67 ModernRomanJUL-37DTPW01.ttf", 0, &face))
        {
            ROSE_CORE_ASSERT(false, "Failed to load font.");
        }    

        FT_Set_Pixel_Sizes(face, 0, size);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        for(unsigned char c = 0; c < 128; c++)
        {
            if(FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                ROSE_CORE_ASSERT(false, "Failed to load glyph.");
                continue;
            }

            unsigned int texture;

            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
             (
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);     
            
            Character character = {
                texture, 
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                face->glyph->advance.x,
                (face->glyph->metrics.height >> 6) - face->glyph->bitmap_top,
                face->glyph->bitmap.width
            };

            characters.insert(std::pair<char, Character>(c, character));         

            // if ((face->glyph->metrics.height >> 6) - face->glyph->bitmap_top > (int)maxDescent) {
            //     maxDescent = (face->glyph->metrics.height >> 6) - face->glyph->bitmap_top;
            // }
        }

        // float x = static_cast<float>(face->ascender) / static_cast<float>(face->units_per_EM);

        // auto y = face->size->metrics.ascender;
        // auto z = face->size->metrics.descender;

        // ROSE_CORE_INFO(maxDescent);
        // ROSE_CORE_INFO(y);
        // ROSE_CORE_INFO(z);

        FT_Done_Face(face);
        FT_Done_FreeType(ft);   
    }
    
    Font::~Font() 
    {   
    }
    
    const std::map<char, Character>& Font::GetCharacters() const
    {
        return characters;   
    }
    
    const float Font::GetMaxBearingY(const std::string& str) const
    {
        float maxYBearing = 0.0f;
        for(const char& c : str) {
            auto character = characters.at(c);
            if(character.Bearing.y > maxYBearing)
                maxYBearing = character.Bearing.y;
        }

        return maxYBearing;
    }
    
    const float Font::GetMinBearingY(const std::string& str) const
    {
        float minYBearing = 0.0f;
        for(const char& c : str) {
            auto character = characters.at(c);
            if(character.Descent > minYBearing)
                minYBearing = character.Descent;
        }

        return minYBearing;
    }
    
    const float Font::GetStringWidth(const std::string& str) const
    {
        float stringWidth = 0.0f;
        for(int i = 0; i < str.length(); ++i) {
            auto character = characters.at(str[i]);
            // stringWidth += i == 0 ? 0 : character.Bearing.x;
            // if(i == str.length()-1)
                stringWidth += character.Advance >> 6;
        }

        return stringWidth;
    }
}