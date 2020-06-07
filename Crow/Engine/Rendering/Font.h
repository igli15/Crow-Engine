//
// Created by Igli milaqi on 03/04/2020.
//

#ifndef CROW_FONT_H
#define CROW_FONT_H

#include <OpenGL/OpenGL.h>
#include "freetype2/ft2build.h"
#include FT_FREETYPE_H
#include <string>
#include <glm/glm.hpp>

//represents glyph data for a character.
struct Character {

    glm::ivec2 size;       // Size of glyph
    glm::ivec2 bearing;    // Offset from baseline to left/top of glyph
    GLuint     textureID;
    GLuint     advance;    // Offset to advance to next glyph
};


class Font {

    friend class TextRenderingSystem;

public:
    void Load(const std::string& path,unsigned int fontSize = 48);
    void SetFontSize(unsigned int newSize);
private:
    unsigned int m_fontSize = 48;
    std::map<GLchar,Character> m_charactersMap;
    FT_Face* m_fontFace = nullptr;
};


#endif //CROW_FONT_H
