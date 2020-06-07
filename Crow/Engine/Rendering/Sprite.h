//
// Created by Igli milaqi on 05/04/2020.
//

#ifndef CROW_SPRITE_H
#define CROW_SPRITE_H


#include <vector>
#include "Texture.h"
class Shader;

class Sprite {

public:
    Texture* texture;

    void Buffer();
    void Render();

    int ID;

private:
    GLuint VAO;
    GLuint m_quadVBO;
};


#endif //CROW_SPRITE_H
