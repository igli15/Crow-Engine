//
// Created by Igli milaqi on 06/05/2020.
//

#ifndef CROW_PROJECTILECOMPONENT_H
#define CROW_PROJECTILECOMPONENT_H


#include <glm/vec3.hpp>

struct ProjectileComponent
{
    glm::vec3 targetPos = {0,0,0};
    float gravity = -1.5f;
    float height = 4;

};


#endif //CROW_PROJECTILECOMPONENT_H
