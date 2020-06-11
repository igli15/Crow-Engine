//
// Created by Igli milaqi on 30/04/2020.
//

#include "EnemySpawnSystem.h"
#include "../../Engine/Debug/Debug.h"
#include "../Worlds/MainWorld.h"
#include "../UnitGroupArchetypes/UnitGroupArchetype.h"
#include "../../Engine/Utils/Random.h"
#include "../../Game/Components/BridgeComponent.h"

void EnemySpawnSystem::Init()
{
    System::Init();

    auto bridgeEntities = world->EntitiesWith<BridgeComponent>();

    for (int i = 0; i < bridgeEntities.size(); ++i)
    {
        BridgeComponent* bridgeComponent = &world->GetComponent<BridgeComponent>(bridgeEntities[i]);
        m_bridges.push_back(bridgeComponent);
    }

    MainWorld* mainWorld = static_cast<MainWorld*>(world);

    WeightedUnit melee {50,mainWorld->GetUnitGroupArchetype<UnitGroupArchetype>("enemyMelee")};
    WeightedUnit tank {30,mainWorld->GetUnitGroupArchetype<UnitGroupArchetype>("enemyTank")};
    WeightedUnit cannon {10,mainWorld->GetUnitGroupArchetype<UnitGroupArchetype>("enemyCannon")};

    m_enemyArchetypes[0] = melee;
    m_enemyArchetypes[1] = tank;
    m_enemyArchetypes[2] = cannon;
}

void EnemySpawnSystem::Update(float dt)
{
    System::Update(dt);

    m_spawnCounter += dt;

    MainWorld* mainWorld = static_cast<MainWorld*>(world);


    int randomIndex = Random::RandomRange(0,3);
    BridgeComponent* randomBridge = m_bridges[randomIndex];

    if(m_spawnCounter > m_spawnTime)
    {
        //mainWorld->GetUnitGroupArchetype<UnitGroupArchetype>("golem")->Build(world, randomBridge);

        WeightedUnit unit = GetRandomUnit();
        unit.archetype->Build(world,randomBridge);
        m_spawnCounter = 0;
    }
}

WeightedUnit EnemySpawnSystem::GetRandomUnit()
{
    float totalWeight= 0;

    for (int i = 0; i < m_enemyArchetypes.size(); ++i)
    {
            totalWeight += m_enemyArchetypes[i].weight;
    }

    float randomWeight = Random::RandomRange(0.0f,totalWeight);

    for (int i = 0; i < m_enemyArchetypes.size(); ++i)
    {
       if(randomWeight <= m_enemyArchetypes[i].weight)
       {
           return m_enemyArchetypes[i];
       }

       randomWeight -= m_enemyArchetypes[i].weight;
    }

    APP_LOG_CRITICAL("Weight Algorithm not working properly..");
    throw;
}
