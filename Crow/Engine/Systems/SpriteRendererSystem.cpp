//
// Created by Igli milaqi on 05/04/2020.
//

#include "SpriteRendererSystem.h"
#include "../Feather/World.h"
#include "../Components/Transform.h"
#include "../Components/SpriteInfo.h"
#include "../Components/Camera.h"


void SpriteRendererSystem::Init()
{
    System::Init();

    m_projectionMatrix = glm::ortho(0.0f, static_cast<GLfloat>(1920),
                                      static_cast<GLfloat>(1080), 0.0f, -1.0f, 1.0f);

    Entity cameraEntity = world->EntitiesWith<Camera>()[0];
    m_cameraTransform = &world->GetComponent<Transform>(cameraEntity);
    m_camera =  &world->GetComponent<Camera>(cameraEntity);

}


void SpriteRendererSystem::Render()
{
    System::Render();

    auto entities = world->EntitiesWith<Transform,SpriteInfo>();

    glm::mat4 camInverseMat = glm::inverse(m_cameraTransform->GetWorldTransform());

    for (int i = 0; i < entities.size(); ++i)
    {
        Transform& transform = world->GetComponent<Transform>(entities[i]);
        SpriteInfo& spriteInfo = world->GetComponent<SpriteInfo>(entities[i]);

        spriteInfo.material->GetShader()->Use();
        spriteInfo.material->BufferShaderUniforms(camInverseMat,m_projectionMatrix,m_cameraTransform->WorldPosition(),world);
        spriteInfo.material->BufferModelUniform(transform.GetWorldTransform());
        spriteInfo.material->BufferMaterialUniforms();
        spriteInfo.sprite->Render();
    }


}

