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
        if(m_renderer->allMaterials[materialIndex]->activeInstanceCount > 0)
        {
            m_renderer->allMaterials[materialIndex]->BufferShaderUniforms(camInverseMat,projection,cameraTransform.WorldPosition(),world);
            m_renderer->allMaterials[materialIndex]->BufferMaterialUniforms();
        }
    }
}
