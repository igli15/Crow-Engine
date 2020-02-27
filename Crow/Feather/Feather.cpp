//
// Created by Igli milaqi on 16/02/2020.
//

#include "Feather.h"
#include "EntityHandle.h"

void Feather::Init()
{
    m_componentManager = new ComponentManager();
    m_entityManager = new EntityManager();
    m_systemManager = new SystemManager();
}

EntityHandle Feather::CreateEntity()
{
    return {m_entityManager->CreateEntity(),this};
}

void Feather::DestroyEntity(Entity entity)
{
    m_entityManager->DestroyEntity(entity);
    m_componentManager->OnEntityDestroyed(entity);
    m_systemManager->OnEntityDestroyed(entity);
}


