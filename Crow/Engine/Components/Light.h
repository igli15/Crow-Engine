//
// Created by Igli milaqi on 17/03/2020.
//

#ifndef CROW_LIGHT_H
#define CROW_LIGHT_H


#include <glm/glm.hpp>

struct Light {

    enum LightType { DIRECTIONAL, POINT, SPOT};

    glm::vec3 color = glm::vec3(1);

    LightType type = DIRECTIONAL;

};


#endif //CROW_LIGHT_H
