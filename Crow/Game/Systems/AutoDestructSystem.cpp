//
// Created by Igli milaqi on 23/05/2020.
//

#include "AutoDestructSystem.h"
#include "../../Engine/Feather/World.h"
#include "../Components/AutoDestructComponent.h"

void AutoDestructSystem::Update(float dt)
{
    System::Update(dt);

    auto entities = world->EntitiesWith<AutoDestructComponent>();

    for (int i = 0; i < entities.size(); ++i)
    {
        AutoDestructComponent& autoDestructComponent = world->GetComponent<AutoDestructComponent>(entities[i]);

        autoDestructComponent.timeCounter += dt;

        if(autoDestructComponent.timeCounter >= autoDestructComponent.destructionTime)
        {
            world->DestroyEntity(entities[i]);
        }
    }
}
