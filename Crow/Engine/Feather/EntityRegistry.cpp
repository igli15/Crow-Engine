//
// Created by Igli milaqi on 14/02/2020.
//

#include "EntityRegistry.h"
#include "../Debug/Debug.h"


EntityRegistry::EntityRegistry()
{
    for (Entity e = 1; e < MAX_ENTITIES; ++e)
    {
        m_entityQueue.push(e);
    }

}

Entity EntityRegistry::CreateEntity()
{
    Debug::Assert(m_activeEntities < MAX_ENTITIES,"Too many Entities");

    Entity id = m_entityQueue.front();
    m_entityQueue.pop();
    m_activeEntities++;

    return id;
}

void EntityRegistry::DestroyEntity(Entity e)
{
    m_signatures[e].reset(); //reset the bitset
    m_entityQueue.push(e); //put it back at the queue
    m_activeEntities--;
}

void EntityRegistry::SetSignature(Entity e, EntitySignature s)
{
    Debug::Assert(e < MAX_ENTITIES, "Entity count can not be negative");
    m_signatures[e]  = s;
}

EntitySignature EntityRegistry::GetSignature(Entity e)
{
    Debug::Assert(e < MAX_ENTITIES, "Entity count can not be negative");

    return m_signatures[e];
}

