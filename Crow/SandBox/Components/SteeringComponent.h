//
// Created by Igli milaqi on 21/04/2020.
//

#ifndef CROW_STEERINGCOMPONENT_H
#define CROW_STEERINGCOMPONENT_H


#include <glm/vec3.hpp>

struct SteeringComponent
{
    float maxSpeed = 6.0f;
    float maxSteeringForce = 10.0f;

    glm::vec3 steering = glm::vec3(0);

};


#endif //CROW_STEERINGCOMPONENT_H
