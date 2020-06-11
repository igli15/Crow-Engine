//
// Created by Igli milaqi on 30/04/2020.
//

#ifndef CROW_ENEMYSPAWNSYSTEM_H
#define CROW_ENEMYSPAWNSYSTEM_H


#include "../../Engine/Feather/System.h"
#include <vector>
#include <array>

class BridgeComponent;
class UnitGroupArchetype;

struct WeightedUnit
{
    float weight = 0;
    UnitGroupArchetype* archetype;
};

class EnemySpawnSystem : public System
{
public:
    void Init() override;
    void Update(float dt) override;

private:
    std::vector<BridgeComponent*> m_bridges;
    float m_spawnCounter = 0.0f;
    float m_spawnTime = 3.0f;

    std::array<WeightedUnit,3> m_enemyArchetypes;

    WeightedUnit GetRandomUnit();

};


#endif //CROW_ENEMYSPAWNSYSTEM_H
