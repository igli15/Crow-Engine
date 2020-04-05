//
// Created by Igli milaqi on 05/04/2020.
//

#ifndef CROW_SPRITERENDERERSYSTEM_H
#define CROW_SPRITERENDERERSYSTEM_H


#include <glm/glm.hpp>
#include "../Feather/System.h"

class SpriteRendererSystem : public System
{
public:
    void Init() override;
    void Render() override;

private:
    glm::mat4 m_projectionMatrix;
};


#endif //CROW_SPRITERENDERERSYSTEM_H
