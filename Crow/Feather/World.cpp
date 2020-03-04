//
// Created by Igli milaqi on 16/02/2020.
//

#include "World.h"
#include "EntityHandle.h"

void World::Init()
{
    m_componentManager = new ComponentManager();
    m_entityManager = new EntityManager();
    m_systemManager = new SystemManager();
}

EntityHandle World::CreateEntity()
{
    return {m_entityManager->CreateEntity(),this};
}

void World::DestroyEntity(Entity entity)
{
    m_entityManager->DestroyEntity(entity);
    m_componentManager->OnEntityDestroyed(entity);
    m_systemManager->OnEntityDestroyed(entity);
}


