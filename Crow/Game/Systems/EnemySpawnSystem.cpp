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
        BridgeComponent* bridgeComponent = m_bridges[0];

        for (int bridgeIndex = 0; bridgeIndex < m_bridges.size(); ++bridgeIndex)
        {
            if(bridgeComponent->playerEntitiesOnBridge.size() < m_bridges[bridgeIndex]->playerEntitiesOnBridge.size())
            {
                bridgeComponent = m_bridges[bridgeIndex];
            }
        }

        WeightedUnit unit = GetRandomUnit();

        if(bridgeComponent->playerEntitiesOnBridge.empty())
        {
            unit.archetype->Build(world,randomBridge);
        } else
        {
            unit.archetype->Build(world,bridgeComponent);
        }


        for (int bridgeIndex = 0; bridgeIndex < m_bridges.size(); ++bridgeIndex)
        {
            if(!m_bridges[bridgeIndex]->playerEntitiesOnBridge.empty() && m_bridges[bridgeIndex]->enemyEntitiesOnBridge.empty())
            {
                unit.archetype->Build(world,m_bridges[bridgeIndex]);
            }
        }

        m_spawnCounter = 0;
    }
}

WeightedUnit EnemySpawnSystem::GetRandomUnit()
{
    float totalWeight= 0.0f;

    for (int archetypeCounter = 0; archetypeCounter < m_enemyArchetypes.size(); ++archetypeCounter)
    {
            totalWeight += m_enemyArchetypes[archetypeCounter].weight;
    }

    float randomWeight = Random::RandomRange(0.0f,totalWeight);

    for (int archetypeCounter = 0; archetypeCounter < m_enemyArchetypes.size(); ++archetypeCounter)
    {
       if(randomWeight <= m_enemyArchetypes[archetypeCounter].weight)
       {
           return m_enemyArchetypes[archetypeCounter];
       }

       randomWeight -= m_enemyArchetypes[archetypeCounter].weight;
    }

    APP_LOG_CRITICAL("Weight Algorithm not working properly..");
    throw;
}
