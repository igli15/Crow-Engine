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
    System::Update(0);

    auto entities = world->EntitiesWith<Transform,RigidBody>();

    for (int i = 0; i < entities.size(); ++i)
    {
        RigidBody& rigidBody = world->GetComponent<RigidBody>(entities[i]);
        Transform& transform = world->GetComponent<Transform>(entities[i]);


        transform.Translate(rigidBody.velocity);
        rigidBody.velocity += rigidBody.acceleration;
    }

}

void MoveSystem::Init()
{
    System::Init();

}

