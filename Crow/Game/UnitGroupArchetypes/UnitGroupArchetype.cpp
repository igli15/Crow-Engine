//
// Created by Igli milaqi on 25/04/2020.
//

#include "UnitGroupArchetype.h"
#include "../../Engine/Components/Transform.h"
#include "../Components/SteeringComponent.h"
#include "../Components/SeekComponent.h"
#include "../../Engine/Components/Rigidbody.h"
#include "../../Game/Components/BridgeComponent.h"
#include "../../Engine/Components/MeshInfo.h"

EntityHandle UnitGroupArchetype::Build(World* world,BridgeComponent* bridge)
{

    EntityHandle unitGroupEntity = world->CreateEntity();
    Transform* unitGroupTransform = unitGroupEntity.AddComponent<Transform>(Transform{});


    EntityHandle unitEntity = world->CreateEntity();

    Transform* transform = unitEntity.AddComponent<Transform>(Transform{});
    transform->SetParent(unitGroupTransform);

    transform->Scale(glm::vec3(scaleFactor));

    unitGroupTransform->Translate(bridge->startPos);

    unitGroupEntity.AddComponent<SteeringComponent>(SteeringComponent{});
    unitGroupEntity.AddComponent<SeekComponent>(SeekComponent{bridge->endPos});
    Rigidbody* rb = unitGroupEntity.AddComponent<Rigidbody>(Rigidbody{});

    unitEntity.AddComponent<MeshInfo>(MeshInfo{unitModel,unitMaterial});

    rb->maxSpeed = maxSpeed;

    return unitEntity;
}
