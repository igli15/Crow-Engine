//
// Created by Igli milaqi on 03/04/2020.
//

#ifndef CROW_TEXT_H
#define CROW_TEXT_H

#include <string>
#include "glm/glm.hpp"
#include "../Rendering/Font.h"

struct Text {

    std::string textString;
    glm::vec3 color = glm::vec3(1);
    float scale = 1;
    Font* font;
};


#endif //CROW_TEXT_H
