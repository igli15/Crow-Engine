//
// Created by Igli milaqi on 30/04/2020.
//

#include "UnitGroupArchetype.h"
#include "../../Engine/Components/Transform.h"
#include "../../Engine/Components/MeshInfo.h"
#include "../Components/UnitAnimationComponent.h"
#include "../../Engine/Utils/Random.h"
#include "../Components/SteeringComponent.h"
#include "../Components/UnitPathComponent.h"
#include "../Components/SeekComponent.h"
#include "../../Engine/Components/Rigidbody.h"
#include "../Components/PlayerUnitCollider.h"
#include "../Components/HealthComponent.h"
#include "../Components/UnitComponent.h"
#include "../Components/EnemyUnitCollider.h"
#include "../Components/CannonComponent.h"
#include "../Components/FloatingComponent.h"
#include "../Components/FlockComponent.h"

void UnitGroupArchetype::Build(World *world, BridgeComponent *bridge)
{
    std::vector<glm::vec3> pathPoints;

    if(!isPlayerUnit)
    {
        for (int i =  bridge->pathPoints.size() -1 ; i >= 0; --i)
        {
            pathPoints.push_back(bridge->pathPoints[i]);
        }
    }
    else
    {
        pathPoints = bridge->pathPoints;
    }

    for (int columnIndex = 0; columnIndex < columns; ++columnIndex)
    {
        for (int rowIndex = 0; rowIndex < rows; ++rowIndex)
        {
            EntityHandle unitEntity = world->CreateEntity();
            Transform *unitTransform = unitEntity.AddComponent<Transform>(Transform{});
            //unitTransform->SetParent(unitGroupEntity.entity);
            unitEntity.AddComponent<MeshInfo>(MeshInfo{unitModel, unitMaterial});
            unitTransform->Scale(glm::vec3(scaleFactor));

            //float randomHeight = Random::RandomRange(5.0f,20.0f)/1000.0f;
            float randomSpeed = Random::RandomRange(animationMinSpeed,animationMaxSpeed);
            unitEntity.AddComponent<UnitAnimationComponent>(UnitAnimationComponent{randomSpeed,animationHeight});
            unitEntity.AddComponent<UnitPathComponent> (UnitPathComponent{pathPoints});

            unitEntity.AddComponent<SteeringComponent>(SteeringComponent{});

            unitEntity.AddComponent<SeekComponent>(SeekComponent{pathPoints[1]});

            Rigidbody* rb = unitEntity.AddComponent<Rigidbody>(Rigidbody{});

            UnitComponent* unitComponent = unitEntity.AddComponent(UnitComponent{});
            unitComponent->bridge = bridge;

            if(isPlayerUnit) {
                unitEntity.AddComponent<PlayerUnitCollider>(PlayerUnitCollider{colliderRadius});
                bridge->playerEntitiesOnBridge.push_back(unitEntity.entity);
                unitTransform->Translate(bridge->pathPoints[0]);
                unitComponent->isPlayerUnit = true;

            } else
            {
                unitEntity.AddComponent<EnemyUnitCollider>(EnemyUnitCollider{colliderRadius});
                bridge->enemyEntitiesOnBridge.push_back(unitEntity.entity);
                unitTransform->Translate(bridge->pathPoints.back());
                unitComponent->isPlayerUnit = false;
            }

            unitComponent->moneyDrop = moneyDrop;
            unitComponent->moneyDropThroughPortal = moneyDropThroughPortal;


            float randomHorizontal = Random::RandomRange(-maxHorizontalDistance,maxHorizontalDistance);
            float randomVertical = Random::RandomRange(-maxVerticalDistance,maxVerticalDistance);

            //unitTransform->Translate(glm::vec3(-(float)columnIndex * randomHorizontal ,0.5f,(float )rowIndex * randomVertical));
            unitTransform->Translate(glm::vec3((columnIndex) * randomHorizontal, 0.2f, (rowIndex) * randomVertical));

            unitEntity.AddComponent<HealthComponent>(HealthComponent{maxHealth,maxHealth});
            unitEntity.AddComponent<DamageDealer>(DamageDealer{damageRate, damageThroughPortal, unitType, strongAgainstType});

            unitEntity.AddComponent<FloatingComponent>(FloatingComponent{});
            unitEntity.AddComponent<FlockComponent>(FlockComponent{});
            rb->maxSpeed = maxSpeed;

            if(unitType == DamageDealer::Jumping)
            {
                CannonComponent cannonComponent{};
                cannonComponent.reloadTime = Random::RandomRange(0.5f,4.0f);
                unitEntity.AddComponent<CannonComponent>(cannonComponent);
            }

        }
    }

}
