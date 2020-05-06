//
// Created by Igli milaqi on 25/03/2020.
//

#include "RigidbodySystem.h"
#include "../../Engine/Feather/World.h"
#include "../../SandBox/Components/MoveComponent.h"
#include "../../Engine/Components/Transform.h"
#include "../../Engine/Events/CollisionEvent.h"
#include "../../Engine/Components/MeshInfo.h"
#include "../../Engine/Rendering/Materials/ColorMaterial.h"
#include "../../Engine/Components/Rigidbody.h"

void RigidbodySystem::Update(float dt)
{
    System::Update(dt);

    auto entities = world->EntitiesWith<Transform,Rigidbody>();

    for (int i = 0; i < entities.size(); ++i)
    {
        Rigidbody& rigidBody = world->GetComponent<Rigidbody>(entities[i]);
        Transform& transform = world->GetComponent<Transform>(entities[i]);


        rigidBody.velocity += rigidBody.acceleration * dt;

        float velocityLength = glm::length(rigidBody.velocity);
        if(velocityLength > rigidBody.maxSpeed)
        {
            rigidBody.velocity = glm::normalize(rigidBody.velocity) * rigidBody.maxSpeed;
        }

        transform.Translate(rigidBody.velocity );
        //rigidBody.acceleration = glm::vec3(0);
    }
}

void RigidbodySystem::Init()
{
    System::Init();

}

