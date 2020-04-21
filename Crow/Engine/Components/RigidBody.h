//
// Created by Igli milaqi on 21/04/2020.
//

#ifndef CROW_RIGIDBODY_H
#define CROW_RIGIDBODY_H


#include <glm/glm.hpp>

struct RigidBody
{
    glm::vec3 velocity = glm::vec3(0);
    glm::vec3 acceleration = glm::vec3(0);
};


#endif //CROW_RIGIDBODY_H
