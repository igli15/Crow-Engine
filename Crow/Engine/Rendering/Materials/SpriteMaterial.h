//
// Created by Igli milaqi on 05/04/2020.
//

#ifndef CROW_SPRITEMATERIAL_H
#define CROW_SPRITEMATERIAL_H


#include "glm/glm.hpp"

class SpriteInfo;
class Shader;

class SpriteMaterial
{
public:
    SpriteMaterial();
    void RenderSprite(SpriteInfo* spriteInfo, const glm::mat4& pModelMatrix, const glm::mat4& pPerspectiveMatrix);

private:
    Shader* shader;
};


#endif //CROW_SPRITEMATERIAL_H
