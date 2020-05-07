//
// Created by Igli milaqi on 30/04/2020.
//

#include "EnemySpawnSystem.h"
#include "../../Engine/Debug/Debug.h"
#include "../Worlds/MainWorld.h"
#include "../UnitGroupArchetypes/AbstractGroupArchetype.h"
#include "../../Engine/Utils/Random.h"
#include "../../Game/Components/BridgeComponent.h"
#include "../UnitGroupArchetypes/EnemyGroupArchetype.h"

void EnemySpawnSystem::Init()
{
    System::Init();

    auto bridgeEntities = world->EntitiesWith<BridgeComponent>();

    for (int i = 0; i < bridgeEntities.size(); ++i)
    {
        BridgeComponent* bridgeComponent = &world->GetComponent<BridgeComponent>(bridgeEntities[i]);
        m_bridges.push_back(bridgeComponent);
    }
}

void EnemySpawnSystem::Update(float dt)
{
    System::Update(dt);

    counter += dt;

    MainWorld* mainWorld = static_cast<MainWorld*>(world);

    int randomIndex = Random::RandomRange(0,3);
    BridgeComponent* randomBridge = m_bridges[randomIndex];

    if(counter > 3)
    {
        EntityHandle entityHandle = mainWorld->GetUnitGroupArchetype<EnemyGroupArchetype>("golem")->Build(world,randomBridge);
        randomBridge->enemyEntitiesOnBridge.push_back(entityHandle.entity);
        counter = 0;
    }
}
