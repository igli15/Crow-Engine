//
// Created by Igli milaqi on 13/06/2020.
//

#include "../../Engine/Core/Input.h"
#include "../../Engine/Feather/World.h"

#include "GameOverSystem.h"
#include "SpawnSystem.h"
#include "EnemySpawnSystem.h"
#include "PlayerMoneySystem.h"
#include "../../Game/Components/BridgeComponent.h"

void GameOverSystem::OnEnable()
{
    System::OnEnable();

    world->DisableSystem<SpawnSystem>();
    world->DisableSystem<EnemySpawnSystem>();
    world->DisableSystem<PlayerMoneySystem>();

    World* tempWorld = world;

    world->ForEach<BridgeComponent>([tempWorld](Entity e,BridgeComponent& bridgeComponent){

        for (int i = 0; i < bridgeComponent.enemyEntitiesOnBridge.size(); ++i)
        {
            tempWorld->DestroyEntity(bridgeComponent.enemyEntitiesOnBridge[i]);
        }

        for (int i = 0; i < bridgeComponent.playerEntitiesOnBridge.size(); ++i)
        {
            tempWorld->DestroyEntity(bridgeComponent.playerEntitiesOnBridge[i]);
        }
    });
}

void GameOverSystem::Update(float dt)
{
    System::Update(dt);

    if(Input::GetKeyDown(GLFW_KEY_R))
    {
        world->DisableSystem<GameOverSystem>();
    }
}

void GameOverSystem::OnDisable()
{
    System::OnDisable();

    world->ResetWorld();
}
