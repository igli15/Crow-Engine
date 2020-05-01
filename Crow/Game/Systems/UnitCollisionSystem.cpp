//
// Created by Igli milaqi on 01/05/2020.
//

#include "UnitCollisionSystem.h"
#include "../../Engine/Components/Transform.h"
#include "../Components/PlayerUnitCollider.h"
#include "../Components/EnemyUnitCollider.h"
#include "../Events/UnitCollisionEvents.h"

void UnitCollisionSystem::Init()
{
    System::Init();
}

void UnitCollisionSystem::Update(float dt)
{
    System::Update(dt);

    m_frameCounter += 1;

    auto playerUnitEntities  = world->EntitiesWith<PlayerUnitCollider>();
    auto enemyUnitEntities = world->EntitiesWith<EnemyUnitCollider>();

    for (int playerUnitIndex = 0; playerUnitIndex < playerUnitEntities.size(); ++playerUnitIndex)
    {
        Transform& playerUnitTransform = world->GetComponent<Transform>(playerUnitEntities[playerUnitIndex]);
        PlayerUnitCollider& playerUnitCollider = world->GetComponent<PlayerUnitCollider>(playerUnitEntities[playerUnitIndex]);

        for (int enemyUnitIndex = 0; enemyUnitIndex < enemyUnitEntities.size(); ++enemyUnitIndex)
        {
            Transform& enemyUnitTransform = world->GetComponent<Transform>(enemyUnitEntities[enemyUnitIndex]);
            EnemyUnitCollider& enemyUnitCollider = world->GetComponent<EnemyUnitCollider>(enemyUnitEntities[enemyUnitIndex]);

            glm::vec3 distanceVector = playerUnitTransform.WorldPosition() - enemyUnitTransform.WorldPosition();
            float distance = glm::length(distanceVector);

            if(distance<= playerUnitCollider.radius * enemyUnitCollider.radius)
            {
                EntityPair entityPair(EntityHandle{playerUnitEntities[playerUnitIndex],world},EntityHandle{enemyUnitEntities[enemyUnitIndex],world});

                auto it = m_collisionMap.find(entityPair);

                if(it != m_collisionMap.end())
                {
                    it->second = m_frameCounter;
                }
                else
                {
                    m_collisionMap.insert(std::pair(entityPair,-m_frameCounter));
                }
            }
        }    
    }

    ThrowCollisionEvents();
}

void UnitCollisionSystem::ThrowCollisionEvents()
{
    for (auto i = m_collisionMap.begin(); i != m_collisionMap.end();)
    {
        if (i->second == -m_frameCounter)
        {
            EventQueue::Instance().Publish(new UnitCollisionEnterEvent{i->first.first,i->first.second});
            i++;

        }
        else if (i->second == m_frameCounter)
        {
            EventQueue::Instance().Publish(new UnitCollisionStayEvent{i->first.first,i->first.second});
            i++;
        }
        else
        {
            EventQueue::Instance().Publish(new UnitCollisionExitEvent{i->first.first,i->first.second});
            i = m_collisionMap.erase(i);
        }
    }
}
