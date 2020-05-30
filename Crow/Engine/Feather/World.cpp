//
// Created by Igli milaqi on 16/02/2020.
//

#include "World.h"
#include "EntityHandle.h"
#include "../Components/Transform.h"
#include "../Components/Camera.h"
#include "../Systems/MeshRendererSystem.h"
#include "../Components/MeshInfo.h"
#include "../Systems/CollisionDetectionSystem.h"
#include "../Events/EntityEvents.h"
#include "../Systems/TransformHierarchySystem.h"
#include "../Systems/TextRenderingSystem.h"
#include "../Systems/MeshRendererSystem.h"
#include "../Systems/SpriteRendererSystem.h"

void World::Init(SystemRegistry* systemRegistry,EntityRegistry* entityRegistry,ComponentRegistry* componentRegistry,PoolRegistry* poolRegistry)
{
    m_componentManager = componentRegistry;
    m_entityManager = entityRegistry;
    m_systemManager = systemRegistry;

    RegisterEngineSystems();
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
        m_allRegisteredSystems[i]->Update(dt);
    }
}

void World::RenderAllSystems()
{
    for (int i = 0; i < m_allRegisteredSystems.size(); ++i)
    {
        m_allRegisteredSystems[i]->Render();
    }
}

void World::Build()
{

}


void World::RegisterEngineSystems()
{
    //RegisterSystem<MeshRendererSystem>();
    RegisterSystem<MeshRendererSystem>();
    RegisterSystem<CollisionDetectionSystem>();
    RegisterSystem<TransformHierarchySystem>();
    RegisterSystem<TextRenderingSystem>();
    RegisterSystem<SpriteRendererSystem>();
    //SetSystemSignature<MeshRendererSystem,Transform,MeshInfo>();
    SetSystemSignature<MeshRendererSystem,Transform,MeshInfo>();

    //SetSystemSignature<CollisionDetectionSystem,Transform,SphereCollider>();

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
        m_allRegisteredSystems[i]->PreRender();
    }
}



