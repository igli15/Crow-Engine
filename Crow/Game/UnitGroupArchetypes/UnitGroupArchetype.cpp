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
    unitGroupTransform->Translate(bridge->startPos);
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            EntityHandle unitEntity = world->CreateEntity();
            Transform *unitTransform = unitEntity.AddComponent<Transform>(Transform{});
            unitTransform->SetParent(unitGroupTransform);
            unitEntity.AddComponent<MeshInfo>(MeshInfo{unitModel, unitMaterial});
            unitTransform->Scale(glm::vec3(scaleFactor));
            unitTransform->SetLocalPosition(glm::vec3((i) * horizontalDistance,0,(j) * verticalDistance));
        }
    }

    unitGroupEntity.AddComponent<SteeringComponent>(SteeringComponent{});
    unitGroupEntity.AddComponent<SeekComponent>(SeekComponent{bridge->endPos});
    Rigidbody* rb = unitGroupEntity.AddComponent<Rigidbody>(Rigidbody{});

    rb->maxSpeed = maxSpeed;

    return unitGroupEntity;
}
