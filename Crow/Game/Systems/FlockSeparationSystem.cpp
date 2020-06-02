//
// Created by Igli milaqi on 19/05/2020.
//

#include "FlockSeparationSystem.h"
#include "../../Engine/Feather/World.h"
#include "../Components/BridgeComponent.h"
#include "../../Engine/Components/Transform.h"
#include "../../Engine/Core/Input.h"
#include "../Components/FlockComponent.h"
#include "../Components/UnitComponent.h"

void FlockSeparationSystem::Init()
{
    System::Init();

    auto bridgeEntities = world->EntitiesWith<BridgeComponent>();

    for (int i = 0; i < bridgeEntities.size(); ++i) {
        BridgeComponent *bridgeComponent = &world->GetComponent<BridgeComponent>(bridgeEntities[i]);
        m_bridges.push_back(bridgeComponent);
    }
}

void FlockSeparationSystem::Update(float dt)
{
    System::Update(dt);

    //m_timeCounter+= dt;
    //if(m_timeCounter >= 0.5f) {

    world->ForEach<SteeringComponent,UnitComponent,FlockComponent,Transform>(
            [&](Entity e,SteeringComponent& steeringComponent,UnitComponent& unitComponent,FlockComponent& flockComponent,Transform& transform)
    {
        if (unitComponent.isPlayerUnit)
        {
            steeringComponent.steering += DoFlockingSeparation(transform,
                    unitComponent.bridge->playerEntitiesOnBridge, flockComponent.separationDistance, flockComponent.separationFactor);
        } else
            {
            steeringComponent.steering += DoFlockingSeparation(transform,
                    unitComponent.bridge->enemyEntitiesOnBridge,  flockComponent.separationDistance, flockComponent.separationFactor);
        }
    });

}

glm::vec3 FlockSeparationSystem::DoFlockingSeparation(Transform& ownTransform, const std::vector<Entity> &others,
                                                      float separationDistance, float separationFactor)
{
    glm::vec3 totalForce{0.0f, 0.0f, 0.0f};
    float sqrSeparationDistance = separationDistance * separationDistance;

    for (int i = 0; i < others.size(); ++i) {
        Entity other = others[i];

        if (ownTransform.owner == other) continue;

        Transform &otherTransform = world->GetComponent<Transform>(other);

        glm::vec3 pos = ownTransform.LocalPosition();
        glm::vec3 otherPos = otherTransform.LocalPosition();

        glm::vec3 delta = pos - otherPos;
        if (glm::length2(delta) <= sqrSeparationDistance) {
            totalForce += pos - otherPos;
        }
    }

    totalForce *= separationFactor;

    return totalForce;
}


