//
// Created by Igli milaqi on 21/04/2020.
//

#ifndef CROW_RIGIDBODY_H
#define CROW_RIGIDBODY_H


#include <glm/glm.hpp>

struct Rigidbody
{
    glm::vec3 velocity = glm::vec3(0);
    glm::vec3 acceleration = glm::vec3(0);
    float maxSpeed = 1.0f;
    float oldSpeed = 0.0f;
};


#endif //CROW_RIGIDBODY_H
