//
// Created by Igli milaqi on 25/03/2020.
//

#include "MoveSystem.h"
#include "../../Engine/Feather/World.h"
#include "../Components/MoveComponent.h"
#include "../../Engine/Components/Transform.h"
#include "../../Engine/Events/CollisionEvent.h"
#include "../../Engine/Components/MeshInfo.h"
#include "../../Engine/Rendering/Materials/ColorMaterial.h"
#include "../../Engine/Components/RigidBody.h"

void MoveSystem::Update(float dt)
{
    System::Update(dt);

    auto entities = world->EntitiesWith<Transform,RigidBody>();

    for (int i = 0; i < entities.size(); ++i)
    {
        RigidBody& rigidBody = world->GetComponent<RigidBody>(entities[i]);
        Transform& transform = world->GetComponent<Transform>(entities[i]);


        rigidBody.velocity += rigidBody.acceleration;

        float velocityLength = glm::length(rigidBody.velocity);
        if(velocityLength > rigidBody.maxSpeed)
        {
            rigidBody.velocity = glm::normalize(rigidBody.velocity) * rigidBody.maxSpeed;
        }

        transform.Translate(rigidBody.velocity);
        //rigidBody.acceleration = glm::vec3(0);
    }

}

void MoveSystem::Init()
{
    System::Init();

}

