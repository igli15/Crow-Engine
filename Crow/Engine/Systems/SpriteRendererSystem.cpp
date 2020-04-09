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
}


void SpriteRendererSystem::Render()
{
    System::Render();

    auto entities = world->EntitiesWith<Transform,SpriteInfo>();

    for (int i = 0; i < entities.size(); ++i)
    {
        Transform& transform = world->GetComponent<Transform>(entities[i]);
        SpriteInfo& spriteInfo = world->GetComponent<SpriteInfo>(entities[i]);

        spriteInfo.material->RenderSprite(&spriteInfo,transform.GetWorldTransform(),m_projectionMatrix);
    }
}
