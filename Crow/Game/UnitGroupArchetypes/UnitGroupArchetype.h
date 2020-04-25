//
// Created by Igli milaqi on 25/04/2020.
//

#ifndef CROW_UNITGROUPARCHETYPE_H
#define CROW_UNITGROUPARCHETYPE_H

#include "../../Engine/Feather/EntityHandle.h"

class Model;
class AbstractMaterial;
class BridgeComponent;

class UnitGroupArchetype
{
public:
    unsigned int rows = 1;
    unsigned int columns = 1;
    unsigned int horizontalDistance = 1;
    unsigned int verticalDistance = 1;
    unsigned int nrOfUnits = 1;

    float scaleFactor = 1.0f;
    float maxSpeed = 0.05f;


    Model* unitModel = nullptr;
    AbstractMaterial* unitMaterial = nullptr;
    BridgeComponent* bridge = nullptr;

    EntityHandle Build(World* world);

};


#endif //CROW_UNITGROUPARCHETYPE_H
