//
// Created by Igli milaqi on 07/05/2020.
//

#include <glm/vec3.hpp>
#include "CannonGroupArchetype.h"
#include "../../Engine/Components/Transform.h"
#include "../../Game/Components/BridgeComponent.h"
#include "../Components/PlayerUnitCollider.h"
#include "../Components/HealthComponent.h"
#include "../../Engine/Components/MeshInfo.h"
#include "../Components/SteeringComponent.h"
#include "../Components/SeekComponent.h"
#include "../../Engine/Components/Rigidbody.h"
#include "../Components/CannonComponent.h"
#include "../Components/UnitComponent.h"

EntityHandle CannonGroupArchetype::Build(World *world, BridgeComponent *bridgeComponent)
{

    EntityHandle cannonEntity = world->CreateEntity();
    Transform* cannonTransform = cannonEntity.AddComponent<Transform>(Transform{});
    cannonTransform->Translate(bridgeComponent->startPos);
    cannonTransform->Translate(glm::vec3(-(float)columns * horizontalDistance / 2, 0.5f, (float )rows * verticalDistance / 2));
    cannonTransform->Scale(glm::vec3(0.06f));
    cannonTransform->Rotate(90,glm::vec3(0,0,1));
    cannonTransform->Rotate(180,glm::vec3(0,1,1));
    cannonEntity.AddComponent<PlayerUnitCollider>(PlayerUnitCollider{colliderRadius});

    cannonEntity.AddComponent<HealthComponent>(HealthComponent{maxHealth, maxHealth});
    cannonEntity.AddComponent<DamageDealer>(DamageDealer{damageRate, unitType, strongAgainstType});
    CannonComponent* cannonComponent = cannonEntity.AddComponent<CannonComponent>(CannonComponent{});
    cannonEntity.AddComponent(UnitComponent{bridgeComponent});

    for (int columnIndex = 0; columnIndex < columns; ++columnIndex)
    {
        for (int rowIndex = 0; rowIndex < rows; ++rowIndex)
        {
            EntityHandle unitEntity = world->CreateEntity();
            Transform *unitTransform = unitEntity.AddComponent<Transform>(Transform{});
            unitTransform->SetParent(cannonEntity.entity);
            unitEntity.AddComponent<MeshInfo>(MeshInfo{unitModel, unitMaterial});
            unitTransform->Scale(glm::vec3(scaleFactor));
            unitTransform->SetLocalPosition(glm::vec3((columnIndex) * horizontalDistance, 0, (rowIndex) * verticalDistance));
        }
    }

    cannonEntity.AddComponent<SteeringComponent>(SteeringComponent{});
    cannonEntity.AddComponent<SeekComponent>(SeekComponent{bridgeComponent->endPos});
    Rigidbody* rb = cannonEntity.AddComponent<Rigidbody>(Rigidbody{});

    rb->maxSpeed = maxSpeed;

    return cannonEntity;
}
