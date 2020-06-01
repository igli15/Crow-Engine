//
// Created by Igli milaqi on 16/02/2020.
//

#include "World.h"
#include "EntityHandle.h"
#include "../Events/EntityEvents.h"
#include "../../Engine/Core/Game.h"

void World::Init(SystemRegistry* systemRegistry,EntityRegistry* entityRegistry,ComponentRegistry* componentRegistry)
{
    m_componentManager = componentRegistry;
    m_entityManager = entityRegistry;
    m_systemManager = systemRegistry;

}

EntityHandle World::CreateEntity()
{
    return {m_entityManager->CreateEntity(),this};
}

void World::InternalDestroyEntity(Entity entity)
{
    m_entityManager->DestroyEntity(entity);
    m_componentManager->OnEntityDestroyed(entity);
    m_systemManager->OnEntityDestroyed(entity);
}

void World::InitAllSystems()
{
    for (int i = 0; i < m_allRegisteredSystems.size(); ++i)
    {
        m_allRegisteredSystems[i]->Init();
    }
}

void World::UpdateAllSystems(float dt)
{
    for (int i = 0; i < m_allRegisteredSystems.size(); ++i)
    {
        System* system = m_allRegisteredSystems[i];

        if(system->enabled) system->Update(dt);
    }
}

void World::RenderAllSystems()
{
    for (int i = 0; i < m_allRegisteredSystems.size(); ++i)
    {
        System* system = m_allRegisteredSystems[i];

        if(system->enabled) system->Render();
    }
}

void World::Build()
{

}


void World::DestroyEntity(Entity entity)
{
    m_entityGarbage.push_back(entity);
    EventQueue::Instance().Publish(new OnEntityDestroyedEvent(entity));
}

void World::ClearEntityGarbage() 
{
    for (int i = m_entityGarbage.size() - 1; i >= 0; i--)
    {
        InternalDestroyEntity(m_entityGarbage[i]);
    }

    m_entityGarbage.clear();
}

void World::PreRenderAllSystems()
{
    for (int i = 0; i < m_allRegisteredSystems.size(); ++i)
    {
        System* system = m_allRegisteredSystems[i];

        if(system->enabled) system->PreRender();
    }
}

void World::ResetWorld()
{
    m_entityManager->ReturnAllEntities();
    m_allRegisteredSystems.clear();
    m_systemManager->ResetAllSystems();
    m_componentManager->RemoveAllComponents();

    Build();
    InitAllSystems();
}



