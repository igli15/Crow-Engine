//
// Created by Igli milaqi on 05/04/2020.
//

#ifndef CROW_SPRITE_H
#define CROW_SPRITE_H


#include "Texture.h"

class Sprite {

public:
    Texture* texture;

    Sprite();
    void Buffer();
    void Render();

private:
    GLuint m_quadVAO;
    GLuint m_quadVBO;
};


#endif //CROW_SPRITE_H
