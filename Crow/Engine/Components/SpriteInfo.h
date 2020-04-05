//
// Created by Igli milaqi on 05/04/2020.
//

#ifndef CROW_SPRITEINFO_H
#define CROW_SPRITEINFO_H


#include "glm/glm.hpp"
#include "../Rendering/Sprite.h"
#include "../Rendering/Materials/SpriteMaterial.h"

struct SpriteInfo {

    glm::vec3 color = glm::vec3(1);
    Sprite* sprite;
    SpriteMaterial* material;

};


#endif //CROW_SPRITEINFO_H
