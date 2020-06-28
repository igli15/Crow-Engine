//
// Created by Igli milaqi on 21/05/2020.
//

#include "FloatingSystem.h"
#include "../../Engine/Feather/World.h"
#include "../../Engine/Components/Transform.h"
#include "../Components/FloatingComponent.h"
#include "../Components/SteeringComponent.h"

void FloatingSystem::Update(float dt)
{
    System::Update(dt);

    auto entities = world->EntitiesWith<Transform,FloatingComponent,SteeringComponent>();

    for (int i = 0; i < entities.size(); ++i)
    {
        Transform& transform = world->GetComponent<Transform>(entities[i]);
        FloatingComponent& floatingBehaviour = world->GetComponent<FloatingComponent>(entities[i]);
        SteeringComponent& steeringComponent = world->GetComponent<SteeringComponent>(entities[i]);

        if(transform.LocalPosition().y < floatingBehaviour.minHeight)
        {
            steeringComponent.steering += glm::vec3(0,floatingBehaviour.heightForce,0);
        }
    }
}
