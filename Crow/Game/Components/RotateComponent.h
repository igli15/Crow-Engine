//
// Created by Igli milaqi on 16/03/2020.
//

#ifndef CROW_ROTATECOMPONENT_H
#define CROW_ROTATECOMPONENT_H


#include <glm/vec3.hpp>

struct RotateComponent {

    glm::vec3 axisOfRotation = {0,1,0};
    float rotateSpeed = 1.0f;
};


#endif //CROW_ROTATECOMPONENT_H
