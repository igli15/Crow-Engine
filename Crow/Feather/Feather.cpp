//
// Created by Igli milaqi on 16/02/2020.
//

#include "Feather.h"

void Feather::Init()
{
    m_componentManager = new ComponentManager();
    m_entityManager = new EntityManager();
    m_systemManager = new SystemManager();
}

Entity Feather::CreateEntity()
{
    return m_entityManager->CreateEntity();
}

void Feather::DestroyEntity(Entity entity)
{
    m_entityManager->DestroyEntity(entity);
    m_componentManager->OnEntityDestroyed(entity);
    m_systemManager->OnEntityDestroyed(entity);
}


