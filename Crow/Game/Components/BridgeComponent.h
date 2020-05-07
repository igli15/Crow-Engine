//
// Created by Igli milaqi on 24/04/2020.
//

#ifndef CROW_BRIDGECOMPONENT_H
#define CROW_BRIDGECOMPONENT_H


#include <glm/vec3.hpp>

#include <vector>
#include "../../Engine/Feather/Types.h"

struct BridgeComponent
{
    std::vector<Entity> playerEntitiesOnBridge;
    std::vector<Entity> enemyEntitiesOnBridge;

    glm::vec3 startPos = {0,0,0};
    glm::vec3 endPos = {0,0,0};
};


#endif //CROW_BRIDGECOMPONENT_H
