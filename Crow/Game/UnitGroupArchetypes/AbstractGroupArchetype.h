//
// Created by Igli milaqi on 30/04/2020.
//

#ifndef CROW_ABSTRACTGROUPARCHETYPE_H
#define CROW_ABSTRACTGROUPARCHETYPE_H

#include "../../Engine/Feather/EntityHandle.h"
#include "../Components/DamageDealer.h"

class Model;
class AbstractMaterial;
class BridgeComponent;

//This acts as the base class for all group archetypes. its similar to a prefab in unity where given a bunch of presets it will build
//an entity.
//This is specific to the gameplay and its not as generic as the prefab implementation.
class AbstractGroupArchetype
{
public:
    unsigned int rows = 1;
    unsigned int columns = 1;
    float horizontalDistance = 1;
    float  verticalDistance = 1;
    float scaleFactor = 1.0f;
    float maxSpeed = 0.05f;
    float maxHealth = 100;
    float damageRate = 0.5f;
    DamageDealer::Type unitType = DamageDealer::Type::NONE;
    DamageDealer::Type strongAgainstType = DamageDealer::Type::NONE;


    Model* unitModel = nullptr;
    AbstractMaterial* unitMaterial = nullptr;

    virtual EntityHandle Build(World* world,BridgeComponent* bridge) = 0;
};


#endif //CROW_ABSTRACTGROUPARCHETYPE_H
