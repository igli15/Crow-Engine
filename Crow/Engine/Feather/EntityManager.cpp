//
// Created by Igli milaqi on 14/02/2020.
//

#include "EntityManager.h"
#include "../Debug/Debug.h"


EntityManager::EntityManager()
{
    for (Entity e = 0; e < MAX_ENTITIES; ++e)
    {
        m_entityQueue.push(e);
    }

    m_signatures = (EntitySignature*)malloc(MAX_ENTITIES * sizeof(EntitySignature));
}

Entity EntityManager::CreateEntity()
{
    Debug::Assert(m_activeEntities < MAX_ENTITIES,"Too many Entities");

    Entity id = m_entityQueue.front();
    m_entityQueue.pop();
    m_activeEntities++;

    return id;
}

void EntityManager::DestroyEntity(Entity e)
{
    Debug::Assert(e < MAX_ENTITIES, "Entity count can not be negative");

    m_signatures[e].reset(); //reset the bitset
    m_entityQueue.push(e); //put it back at the queue
    m_activeEntities--;
}

void EntityManager::SetSignature(Entity e, EntitySignature s)
{
    Debug::Assert(e < MAX_ENTITIES, "Entity count can not be negative");
    m_signatures[e]  = s;
}

EntitySignature EntityManager::GetSignature(Entity e)
{
    Debug::Assert(e < MAX_ENTITIES, "Entity count can not be negative");

    return m_signatures[e];
}

