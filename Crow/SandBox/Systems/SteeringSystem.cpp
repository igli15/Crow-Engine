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

void SteeringSystem::Update(float dt)
{
    System::Update(0);

    auto entities = world->EntitiesWith<RigidBody,SteeringComponent>();

    for (int entityIndex = 0; entityIndex < entities.size(); ++entityIndex)
    {

        RigidBody &rigidBody = world->GetComponent<RigidBody>(entities[entityIndex]);
        SteeringComponent &steeringComponent = world->GetComponent<SteeringComponent>(entities[entityIndex]);

        //Clamp steering
        if(steeringComponent.maxSteeringForce > 0)
        {

            float steeringLength = glm::length(steeringComponent.steering);
            if(steeringLength > steeringComponent.maxSteeringForce)
            {
                steeringComponent.steering = glm::normalize(steeringComponent.steering) * steeringComponent.maxSteeringForce;
            }

        }

        //add steering to the acceleration
        rigidBody.acceleration += steeringComponent.steering;

        steeringComponent.steering = glm::vec3(0);
    }
}
