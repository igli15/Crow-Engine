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

void World::Init()
{
    m_componentManager = new ComponentManager();
    m_entityManager = new EntityManager();
    m_systemManager = new SystemManager();
    eventQueue = new EventQueue();

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

void World::UpdateAllSystems()
{
    for (int i = 0; i < m_allRegisteredSystems.size(); ++i)
    {
        m_allRegisteredSystems[i]->Update();
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
    CreateCamera();
}

void World::CreateCamera()
{
    cameraEntity = new EntityHandle();
    cameraEntity->entity = m_entityManager->CreateEntity();
    cameraEntity->feather = this;

    cameraEntity->AddComponent<Camera>(Camera{});
    cameraEntity->AddComponent<Transform>(Transform{});
}

void World::RegisterEngineSystems()
{
    RegisterSystem<MeshRendererSystem>();
    RegisterSystem<CollisionDetectionSystem>();
    SetSystemSignature<MeshRendererSystem,Transform,MeshInfo>();

    //SetSystemSignature<CollisionDetectionSystem,Transform,SphereCollider>();

}

void World::DestroyEntity(Entity entity)
{
    m_entityGarbage.push_back(entity);
}

void World::ClearEntityGarbage() 
{
    for (int i = m_entityGarbage.size() - 1; i >= 0; i--)
    {
        InternalDestroyEntity(m_entityGarbage[i]);
    }

    m_entityGarbage.clear();
}



