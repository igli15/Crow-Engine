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

    Sprite();
    void Buffer();
    void BufferModelMatrices(std::vector<glm::mat4>& modelMatrices);
    void Render(int amount,Shader* shader);

    int ID;

private:
    GLuint VAO;
    GLuint m_quadVBO;
    GLuint m_modelsVBO;
};


#endif //CROW_SPRITE_H
