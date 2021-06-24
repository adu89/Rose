#include "Font.h"

#include <glad/glad.h>

namespace Rose {
    Font::Font() 
    {
        FT_Library ft;
        if(FT_Init_FreeType(&ft)) {
            ROSE_CORE_ASSERT(false, "Could not initialise FreeType library.");
        }
        
        FT_Face face;
        if (FT_New_Face(ft, "BigShouldersStencilDisplay-Bold.ttf", 0, &face))
        {
            ROSE_CORE_ASSERT(false, "Failed to load font.");
        }    

        FT_Set_Pixel_Sizes(face, 0, 48);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        for(unsigned char c = 0; c < 128; c++)
        {
            ROSE_INFO(c);

            if(FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                ROSE_CORE_ASSERT(false, "Failed to load glyph.");
                continue;
            }

            unsigned int texture;

            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
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
                face->glyph->advance.x
            };

            characters.insert(std::pair<char, Character>(c, character));         
        }

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
}