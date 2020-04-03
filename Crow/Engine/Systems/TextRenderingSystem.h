//
// Created by Igli milaqi on 03/04/2020.
//

#ifndef CROW_TEXTRENDERINGSYSTEM_H
#define CROW_TEXTRENDERINGSYSTEM_H


#include <OpenGL/OpenGL.h>
#include <map>
#include "../Feather/System.h"
#include "glm/glm.hpp"

//represents glyph data for a character.
struct Character {

    glm::ivec2 size;       // Size of glyph
    glm::ivec2 bearing;    // Offset from baseline to left/top of glyph
    GLuint     textureID;
    GLuint     advance;    // Offset to advance to next glyph
};


class TextRenderingSystem : public System {

public:
    void Init() override;

private:
    void BufferAllTextComponents();

    std::map<GLchar,Character> m_charactersMap;
};


#endif //CROW_TEXTRENDERINGSYSTEM_H
