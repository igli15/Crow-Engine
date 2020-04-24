//
// Created by Igli milaqi on 24/04/2020.
//

#ifndef CROW_BRIDGECOMPONENT_H
#define CROW_BRIDGECOMPONENT_H


#include <glm/vec3.hpp>


struct BridgeComponent
{
    glm::vec3 startPos = {0,0,0};
    glm::vec3 endPos = {0,0,0};
    bool isSelected = false;
};


#endif //CROW_BRIDGECOMPONENT_H
