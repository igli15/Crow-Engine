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

    auto entities = world->EntitiesWith<FlockComponent, UnitComponent, SteeringComponent>();

    /*
    if(Input::GetKeyDown(GLFW_KEY_SPACE))
    {
        APP_LOG(entities.size());
    }
     */

    for (int i = 0; i < entities.size(); ++i) {
        SteeringComponent &steeringComponent = world->GetComponent<SteeringComponent>(entities[i]);
        UnitComponent &unitComponent = world->GetComponent<UnitComponent>(entities[i]);
        FlockComponent &flockSeparationComponent = world->GetComponent<FlockComponent>(entities[i]);

        if (unitComponent.isPlayerUnit) {
            steeringComponent.steering += DoFlockingSeparation(entities[i],
                                                               unitComponent.bridge->playerEntitiesOnBridge, flockSeparationComponent.separationDistance, flockSeparationComponent.separationFactor);
        } else {
            steeringComponent.steering += DoFlockingSeparation(entities[i],
                                                               unitComponent.bridge->enemyEntitiesOnBridge,  flockSeparationComponent.separationDistance, flockSeparationComponent.separationFactor);
        }

    }
}

glm::vec3 FlockSeparationSystem::DoFlockingSeparation(Entity currentEntity, const std::vector<Entity> &others,
                                                      float separationDistance, float separationFactor)
{
    glm::vec3 totalForce{0, 0, 0};
    float sqrSeparationDistance = separationDistance * separationDistance;

    Transform &ownTransform = world->GetComponent<Transform>(currentEntity);

    for (int i = 0; i < others.size(); ++i) {
        Entity other = others[i];

        if (currentEntity == other) continue;

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


