//
// Created by Igli milaqi on 19/05/2020.
//

#include "FlockSeparationSystem.h"
#include "../../Engine/Feather/World.h"
#include "../Components/BridgeComponent.h"
#include "../../Engine/Components/Transform.h"
#include "../../Engine/Core/Input.h"

void FlockSeparationSystem::Init()
{
    System::Init();

    auto bridgeEntities = world->EntitiesWith<BridgeComponent>();

    for (int i = 0; i < bridgeEntities.size(); ++i)
    {
        BridgeComponent* bridgeComponent = &world->GetComponent<BridgeComponent>(bridgeEntities[i]);
        m_bridges.push_back(bridgeComponent);
    }
}

void FlockSeparationSystem::Update(float dt)
{
    System::Update(dt);

    //m_timeCounter+= dt;
    //if(m_timeCounter >= 0.5f) {

        for (int i = 0; i < m_bridges.size(); ++i) {
            BridgeComponent *bridge = m_bridges[i];

            for (int j = 0; j < bridge->playerEntitiesOnBridge.size(); ++j) {
                SteeringComponent &steeringComponent = world->GetComponent<SteeringComponent>(
                        bridge->playerEntitiesOnBridge[j]);
                steeringComponent.steering += DoFlockingSeparation(bridge->playerEntitiesOnBridge[j],
                                                                   bridge->playerEntitiesOnBridge, 0.2f, 10);
            }

            //std::vector<SteeringComponent*> enemySteerings;


        }
        m_timeCounter = 0;
   // }
}

glm::vec3 FlockSeparationSystem::DoFlockingSeparation(Entity currentEntity, const std::vector<Entity>& others,
                                                      float separationDistance, float separationFactor)
{
    glm::vec3 totalForce {0,0,0};
    float sqrSeparationDistance = separationDistance * separationDistance;

    Transform& ownTransform = world->GetComponent<Transform>(currentEntity);

    for (int i = 0; i < others.size(); ++i)
    {
        Entity other = others[i];

        if(currentEntity == other) continue;

        Transform& otherTransform = world->GetComponent<Transform>(other);

        glm::vec3 pos = ownTransform.LocalPosition();
        glm::vec3 otherPos = otherTransform.LocalPosition();

        glm::vec3 delta = pos - otherPos;
        if (glm::length2(delta) <= sqrSeparationDistance)
        {
            totalForce += pos - otherPos;
        }
    }

    totalForce *= separationFactor;

    return totalForce;
}


