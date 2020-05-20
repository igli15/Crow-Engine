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
#include "../Components/PlayerUnitCollider.h"
#include "../Components/HealthComponent.h"
#include "../Components/DamageDealer.h"
#include "../Components/UnitComponent.h"
#include "../Components/UnitPathComponent.h"
#include "../Components/UnitAnimationComponent.h"
#include "../../Engine/Utils/Random.h"

EntityHandle UnitGroupArchetype::Build(World* world,BridgeComponent* bridge)
{
    EntityHandle unitGroupEntity = world->CreateEntity();
    Transform* unitGroupTransform = unitGroupEntity.AddComponent<Transform>(Transform{});
    unitGroupTransform->Translate(bridge->pathPoints[0]);
    unitGroupTransform->Translate(glm::vec3(-(float)columns * horizontalDistance/2,0.5f,(float )rows * verticalDistance/2));

    std::vector<glm::vec3> pathPoints = bridge->pathPoints;
    //unitGroupEntity.AddComponent<UnitPathComponent>(UnitPathComponent{pathPoints});

    for (int columnIndex = 0; columnIndex < columns; ++columnIndex)
    {
        for (int rowIndex = 0; rowIndex < rows; ++rowIndex)
        {
            EntityHandle unitEntity = world->CreateEntity();
            Transform *unitTransform = unitEntity.AddComponent<Transform>(Transform{});
            unitTransform->Translate(bridge->pathPoints[0]);
            //unitTransform->SetParent(unitGroupEntity.entity);
            unitEntity.AddComponent<MeshInfo>(MeshInfo{unitModel, unitMaterial});
            unitTransform->Scale(glm::vec3(scaleFactor));
            unitTransform->Translate(glm::vec3((columnIndex) * horizontalDistance, 0, (rowIndex) * verticalDistance));

            //float randomHeight = Random::RandomRange(5.0f,20.0f)/1000.0f;
            float randomSpeed = Random::RandomRange(animationMinSpeed,animationMaxSpeed);
            unitEntity.AddComponent<UnitAnimationComponent>(UnitAnimationComponent{randomSpeed,animationHeight});
            unitEntity.AddComponent<UnitPathComponent>(UnitPathComponent{pathPoints});

            unitEntity.AddComponent<SteeringComponent>(SteeringComponent{});

            unitEntity.AddComponent<SeekComponent>(SeekComponent{bridge->pathPoints[1]});
            Rigidbody* rb = unitEntity.AddComponent<Rigidbody>(Rigidbody{});

            unitEntity.AddComponent<PlayerUnitCollider>(PlayerUnitCollider{colliderRadius});

            unitEntity.AddComponent<HealthComponent>(HealthComponent{maxHealth/(rows*columns),maxHealth/(rows*columns)});
            unitEntity.AddComponent<DamageDealer>(DamageDealer{damageRate,unitType,strongAgainstType});
            unitEntity.AddComponent(UnitComponent{bridge});

            rb->maxSpeed = maxSpeed;

            bridge->playerEntitiesOnBridge.push_back(unitEntity.entity);

        }
    }


    return unitGroupEntity;
}
