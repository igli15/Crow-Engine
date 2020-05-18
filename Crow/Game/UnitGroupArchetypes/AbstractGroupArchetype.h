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
    float horizontalDistance = 1.0f;
    float  verticalDistance = 1.0f;
    float scaleFactor = 1.0f;
    float maxSpeed = 0.05f;
    float maxHealth = 100.0f;
    float damageRate = 0.5f;
    float colliderRadius = 1.0f;

    float animationMinSpeed = 8.0f;
    float animationMaxSpeed = 12.0f;
    float animationHeight = 0.003f;

    DamageDealer::Type unitType = DamageDealer::Type::NONE;
    DamageDealer::Type strongAgainstType = DamageDealer::Type::NONE;


    Model* unitModel = nullptr;
    AbstractMaterial* unitMaterial = nullptr;

    virtual EntityHandle Build(World* world,BridgeComponent* bridge) = 0;
};


#endif //CROW_ABSTRACTGROUPARCHETYPE_H
