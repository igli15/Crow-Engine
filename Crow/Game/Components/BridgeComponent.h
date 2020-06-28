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

    std::vector<glm::vec3> pathPoints;


};


#endif //CROW_BRIDGECOMPONENT_H
