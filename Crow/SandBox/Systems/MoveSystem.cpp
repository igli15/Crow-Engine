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

void MoveSystem::Update()
{
    System::Update();

    auto entities = world->EntitiesWith<Transform,MoveComponent>();

    for (int i = 0; i < entities.size(); ++i)
    {
        MoveComponent& moveComponent = world->GetComponent<MoveComponent>(entities[i]);
        Transform& transform = world->GetComponent<Transform>(entities[i]);

        transform.Translate(moveComponent.direction * moveComponent.speed);
    }
}

void MoveSystem::Init()
{
    System::Init();

    world->eventQueue->Subscribe(this,&MoveSystem::UpdateMaterials);
}

void MoveSystem::UpdateMaterials(CollisionEvent* collisionEvent)
{
    static_cast<ColorMaterial*>(collisionEvent->entity1.GetComponent<MeshInfo>().component->material)->mainColor = glm::vec3(1,0,0);
}
