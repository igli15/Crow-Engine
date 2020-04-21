//
// Created by Igli milaqi on 21/04/2020.
//

#include "SteeringSystem.h"
#include "../../Engine/Feather/World.h"
#include "../../Engine/Components/Transform.h"
#include "../../Engine/Components/RigidBody.h"
#include "../Components/SteeringComponent.h"

void SteeringSystem::Init()
{
    System::Init();
}

void SteeringSystem::Update()
{
    System::Update();

    auto entities = world->EntitiesWith<RigidBody,SteeringComponent>();

    for (int entityIndex = 0; entityIndex < entities.size(); ++entityIndex)
    {
        RigidBody &rigidBody = world->GetComponent<RigidBody>(entities[entityIndex]);
        SteeringComponent &steeringComponent = world->GetComponent<SteeringComponent>(entities[entityIndex]);

        rigidBody.acceleration = steeringComponent.steering;
        rigidBody.velocity = glm::clamp(rigidBody.velocity,0.0f,steeringComponent.maxSpeed);
        steeringComponent.steering = glm::vec3(0);
    }
}
