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

    SpriteInfo(){};
    SpriteInfo(Sprite* pSprite,AbstractMaterial* pMaterial,glm::vec3 pColor = glm::vec3(1))
    {
        SetMaterial(pMaterial);
        material = pMaterial;
        sprite = pSprite;
        SetColor(pColor);
    };

    void SetMaterial(AbstractMaterial* newMat)
    {
        if(material == newMat)
        {
            ENGINE_LOG_WARNING("Assigning the same material to sprite info");
            return;
        }

        if(material!= nullptr)
        {
            ENGINE_LOG_WARNING("Assigning null material to sprite info");
            material->activeInstanceCount -= 1;
        }

        material = newMat;
        material->activeInstanceCount += 1;

    };

    void SetColor(const glm::vec3& newColor)
    {
        color = newColor;
        static_cast<SpriteMaterial*>(material)->color = newColor;
    }

    AbstractMaterial* GetMaterial()
    {
        return material;
    };

private:
    glm::vec3 color = glm::vec3(1);
    AbstractMaterial* material = nullptr;

};


#endif //CROW_SPRITEINFO_H
