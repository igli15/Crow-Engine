//
// Created by Igli milaqi on 30/04/2020.
//

#include "EnemyGroupArchetype.h"
#include "../../Engine/Components/Transform.h"
#include "../../Engine/Components/MeshInfo.h"
#include "../Components/SteeringComponent.h"
#include "../Components/SeekComponent.h"
#include "../../Engine/Components/Rigidbody.h"
#include "../../Game/Components/BridgeComponent.h"
#include "../Components/EnemyUnitCollider.h"
#include "../Components/HealthComponent.h"


EntityHandle EnemyGroupArchetype::Build(World *world, BridgeComponent *bridge)
{
    EntityHandle unitGroupEntity = world->CreateEntity();
    unitGroupEntity.AddComponent<EnemyUnitCollider>(EnemyUnitCollider{colliderRadius});
    Transform* unitGroupTransform = unitGroupEntity.AddComponent<Transform>(Transform{});
    unitGroupTransform->Translate(bridge->endPos);
    unitGroupTransform->Translate(glm::vec3(0,1,0));

    unitGroupEntity.AddComponent<HealthComponent>(HealthComponent{maxHealth,maxHealth});
    unitGroupEntity.AddComponent<DamageDealer>(DamageDealer{damageRate,unitType,strongAgainstType});

    for (int columnIndex = 0; columnIndex < columns; ++columnIndex)
    {
        for (int rowIndex = 0; rowIndex < rows; ++rowIndex)
        {
            EntityHandle unitEntity = world->CreateEntity();
            Transform *unitTransform = unitEntity.AddComponent<Transform>(Transform{});
            unitTransform->SetParent(unitGroupEntity.entity);
            unitEntity.AddComponent<MeshInfo>(MeshInfo{unitModel, unitMaterial});
            unitTransform->Scale(glm::vec3(scaleFactor));
            unitTransform->SetLocalPosition(glm::vec3((columnIndex) * horizontalDistance, 0, (rowIndex) * verticalDistance));
        }
    }

    unitGroupEntity.AddComponent<SteeringComponent>(SteeringComponent{});
    unitGroupEntity.AddComponent<SeekComponent>(SeekComponent{bridge->startPos});
    Rigidbody* rb = unitGroupEntity.AddComponent<Rigidbody>(Rigidbody{});

    rb->maxSpeed = maxSpeed;

    return unitGroupEntity;
}
