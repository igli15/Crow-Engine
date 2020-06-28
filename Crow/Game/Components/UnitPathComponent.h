//
// Created by Igli milaqi on 17/05/2020.
//

#ifndef CROW_UNITPATHCOMPONENT_H
#define CROW_UNITPATHCOMPONENT_H

#include <vector>
#include <glm/vec3.hpp>

struct UnitPathComponent
{
    std::vector<glm::vec3> pathPoints;
    unsigned int currentPathIndex = 0;
};


#endif //CROW_UNITPATHCOMPONENT_H
