//
// Created by Igli milaqi on 06/05/2020.
//

#ifndef CROW_PROJECTILECOMPONENT_H
#define CROW_PROJECTILECOMPONENT_H


#include <glm/vec3.hpp>

struct ProjectileComponent
{
    glm::vec3 targetPos = {0,0,0};
    float gravity = -0.05f;
    float height = 7;

};


#endif //CROW_PROJECTILECOMPONENT_H
