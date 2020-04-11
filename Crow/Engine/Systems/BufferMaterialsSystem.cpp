//
// Created by Igli milaqi on 10/04/2020.
//

#include "BufferMaterialsSystem.h"
#include "../Core/Game.h"
#include "../Core/Renderer.h"
#include "../Components/Camera.h"
#include "../Components/Transform.h"

void BufferMaterialsSystem::Init()
{
    System::Init();

    m_renderer = Game::Instance()->renderer;

}


void BufferMaterialsSystem::PreRender()
{
    System::PreRender();

    Entity cameraEntity = world->EntitiesWith<Camera>()[0];
    Transform& cameraTransform = world->GetComponent<Transform>(cameraEntity);
    Camera& camera=  world->GetComponent<Camera>(cameraEntity);

    glm::mat4 camInverseMat = glm::inverse(cameraTransform.GetWorldTransform());
    glm::mat4 projection = camera.GetProjection();


    for (int shaderIndex = 0; shaderIndex < m_renderer->allShaders.size(); ++shaderIndex)
    {
        m_renderer->allShaders[shaderIndex]->bufferedThisFrame = false;
    }

    for (int materialIndex = 0; materialIndex < m_renderer->allMaterials.size(); ++materialIndex)
    {
        AbstractMaterial* material =m_renderer->allMaterials[materialIndex];

        if(material->activeInstanceCount > 0)
        {
            if(material->m_shader->bufferedThisFrame != true)
            {
               material->BufferShaderUniforms(camInverseMat, projection,cameraTransform.WorldPosition(), world);
            }
           material->BufferMaterialUniforms();
        }
    }
}

void BufferMaterialsSystem::OnSpriteInfoRemoved(ComponentRemovedEvent<SpriteInfo> *event)
{
    event->component.GetMaterial()->activeInstanceCount -=1;
}

void BufferMaterialsSystem::OnMeshInfoRemoved(ComponentRemovedEvent<MeshInfo> *event)
{
    event->component.GetMaterial()->activeInstanceCount -=1;
}

void BufferMaterialsSystem::OnCreate()
{
    System::OnCreate();

    EventQueue::Instance().Subscribe(this, &BufferMaterialsSystem::OnSpriteInfoRemoved);
    EventQueue::Instance().Subscribe(this, &BufferMaterialsSystem::OnMeshInfoRemoved);
}
