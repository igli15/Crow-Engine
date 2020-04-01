//
// Created by Igli milaqi on 25/03/2020.
//

#include "CollisionDetectionSystem.h"
#include "../Components/Transform.h"
#include "../Feather/World.h"
#include "../Components/SphereCollider.h"
#include "../Events/CollisionEvent.h"
#include "../Events/CollisionEnterEvent.h"
#include "../Events/CollisionExitEvent.h"

void CollisionDetectionSystem::Update()
{
    System::Update();

    m_frameCounter += 1;

    auto entities = world->EntitiesWith<Transform,SphereCollider>();

    for (int firstEntityIndex = 0; firstEntityIndex < entities.size(); firstEntityIndex++)
    {
        Transform& t1 = world->GetComponent<Transform>(entities[firstEntityIndex]);
        SphereCollider& s1 = world->GetComponent<SphereCollider>(entities[firstEntityIndex]);
        for (int nextEntityIndex = firstEntityIndex + 1; nextEntityIndex < entities.size(); nextEntityIndex++)
        {
            Transform& t2 = world->GetComponent<Transform>(entities[nextEntityIndex]);

            SphereCollider& s2 = world->GetComponent<SphereCollider>(entities[nextEntityIndex]);

            glm::vec3 distanceVector = t1.LocalPosition() - t2.LocalPosition();
            float distance = glm::length(distanceVector);

            if(distance<= s1.radius * s2.radius)
            {
                EntityPair entityPair(EntityHandle{entities[firstEntityIndex],world},EntityHandle{entities[nextEntityIndex],world});

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

void CollisionDetectionSystem::ThrowCollisionEvents()
{
    for (auto i = m_collisionMap.begin(); i != m_collisionMap.end();)
    {
        if (i->second == -m_frameCounter)
        {
            EventQueue::Instance().Publish(new CollisionEnterEvent{i->first.first,i->first.second});
            i++;

        }
        else if (i->second == m_frameCounter)
        {
            EventQueue::Instance().Publish(new CollisionEvent{i->first.first,i->first.second});
            i++;
        }
        else
        {
            EventQueue::Instance().Publish(new CollisionExitEvent{i->first.first,i->first.second});
            i = m_collisionMap.erase(i);
        }
    }

}
