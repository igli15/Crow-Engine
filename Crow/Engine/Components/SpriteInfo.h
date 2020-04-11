//
// Created by Igli milaqi on 05/04/2020.
//

#ifndef CROW_SPRITEINFO_H
#define CROW_SPRITEINFO_H


#include "glm/glm.hpp"
#include "../Rendering/Sprite.h"
#include "../Rendering/AbstractMaterial.h"

struct SpriteInfo {

    glm::vec3 color = glm::vec3(1);
    Sprite* sprite;

    void SetMaterial(AbstractMaterial* newMat)
    {
        if(material == newMat) return;

        if(material!= nullptr) material->activeInstanceCount -= 1;

        material = newMat;
        material->activeInstanceCount += 1;

    };

    AbstractMaterial* GetMaterial()
    {
        return material;
    };

private:
    AbstractMaterial* material;

};


#endif //CROW_SPRITEINFO_H
