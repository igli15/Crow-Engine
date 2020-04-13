//
// Created by Igli milaqi on 05/04/2020.
//

#ifndef CROW_SPRITEINFO_H
#define CROW_SPRITEINFO_H


#include "glm/glm.hpp"
#include "../Rendering/Sprite.h"
#include "../Rendering/AbstractMaterial.h"
#include "../Rendering/Materials/SpriteMaterial.h"

struct SpriteInfo {

    Sprite* sprite;
    AbstractMaterial* material = nullptr;

    SpriteInfo(){};
    SpriteInfo(Sprite* pSprite,AbstractMaterial* pMaterial,glm::vec3 pColor = glm::vec3(1)) : sprite(pSprite),material(pMaterial),color(pColor)
    {
    };


    void SetColor(const glm::vec3& newColor)
    {
        color = newColor;
        static_cast<SpriteMaterial*>(material)->color = newColor;
    }


private:
    glm::vec3 color = glm::vec3(1);

};


#endif //CROW_SPRITEINFO_H
