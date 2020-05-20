//
// Created by Igli milaqi on 30/04/2020.
//

#ifndef CROW_UNITGROUPARCHETYPE_H
#define CROW_UNITGROUPARCHETYPE_H

#include "../../Engine/Feather/EntityHandle.h"
#include "../Components/DamageDealer.h"

class Model;
class AbstractMaterial;
class BridgeComponent;

//This acts as the base for all group archetypes. its similar to a prefab in unity where given a bunch of presets it will build
//an entity.
//This is specific to the gameplay and its not as generic as the prefab implementation.
class UnitGroupArchetype
{
public:
    unsigned int rows = 1;
    unsigned int columns = 1;

    float maxHorizontalDistance = 1.0f;
    float maxVerticalDistance = 1.0f;

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

    bool isPlayerUnit = true;

    virtual void Build(World* world,BridgeComponent* bridge);
};


#endif //CROW_UNITGROUPARCHETYPE_H
