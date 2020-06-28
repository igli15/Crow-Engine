//
// Created by Igli milaqi on 21/04/2020.
//

#ifndef CROW_STEERINGCOMPONENT_H
#define CROW_STEERINGCOMPONENT_H


#include <glm/vec3.hpp>

struct SteeringComponent
{
    glm::vec3 steering = glm::vec3(0.0f);
    float maxSteeringForce = 10.0f;
    float rotationAngleStep = 30.0f;
    bool rotateTowardsVelocity = true;

};


#endif //CROW_STEERINGCOMPONENT_H
