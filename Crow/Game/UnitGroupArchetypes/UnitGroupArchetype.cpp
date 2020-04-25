//
// Created by Igli milaqi on 25/04/2020.
//

#include "UnitGroupArchetype.h"
#include "../../Engine/Components/Transform.h"
#include "../Components/SteeringComponent.h"
#include "../Components/SeekComponent.h"
#include "../../Engine/Components/Rigidbody.h"
#include "../../Game/Components/BridgeComponent.h"

EntityHandle UnitGroupArchetype::Build(World* world)
{
    EntityHandle entityHandle = world->CreateEntity();

    Transform* transform = entityHandle.AddComponent<Transform>(Transform{});
    transform->Translate(bridge->startPos);
    transform->Scale(glm::vec3(scaleFactor));

    entityHandle.AddComponent<SteeringComponent>(SteeringComponent{});
    entityHandle.AddComponent<SeekComponent>(SeekComponent{bridge->endPos});
    Rigidbody* rb = entityHandle.AddComponent<Rigidbody>(Rigidbody{});
    rb->maxSpeed = maxSpeed;

    return entityHandle;
}
