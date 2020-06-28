//
// Created by Igli milaqi on 17/03/2020.
//

#ifndef CROW_LIGHT_H
#define CROW_LIGHT_H


#include <glm/glm.hpp>

struct Light {

    enum LightType { DIRECTIONAL, POINT, SPOT};

    glm::vec3 color = glm::vec3(1);

    float intensity = 1;

    float constant = 1;
    float linear = 0.09f;
    float quadratic = 0.032f;

    float cutoff = 25;
    float outerCutoff = 35;

    LightType type = DIRECTIONAL;

};


#endif //CROW_LIGHT_H
