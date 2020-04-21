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

void MoveSystem::Update()
{
    System::Update();

    auto entities = world->EntitiesWith<Transform,MoveComponent,RigidBody>();

    for (int i = 0; i < entities.size(); ++i)
    {
        MoveComponent& moveComponent = world->GetComponent<MoveComponent>(entities[i]);
        RigidBody& rigidBody = world->GetComponent<RigidBody>(entities[i]);
        Transform& transform = world->GetComponent<Transform>(entities[i]);


        transform.Translate(rigidBody.velocity);
        rigidBody.velocity += rigidBody.acceleration;
        rigidBody.velocity = glm::clamp(rigidBody.velocity,-moveComponent.speed,moveComponent.speed);

    }

}

void MoveSystem::Init()
{
    System::Init();

}

