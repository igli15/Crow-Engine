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

    for (auto pair: m_instancedModelMap)
    {
        pair.second.modelMatrices->clear();
    }

    for (int i = 0; i < entities.size(); ++i)
    {
        Transform& transform = world->GetComponent<Transform>(entities[i]);
        SpriteInfo& spriteInfo = world->GetComponent<SpriteInfo>(entities[i]);

        m_instancedModelMap[spriteInfo.sprite->ID].modelMatrices->push_back(transform.GetWorldTransform());
    }

    for (auto pair: m_instancedModelMap)
    {
        //Buffer the all model matrices VBO to the shader
        pair.second.sprite->BufferModelMatrices(*pair.second.modelMatrices);

        pair.second.sprite->Render(pair.second.modelMatrices->size());
    }
}

void SpriteRendererSystem::OnSpriteInfoAdded(ComponentAddedEvent<SpriteInfo> *event)
{
    int ID = event->component->sprite->ID;
    auto iterator = m_instancedModelMap.find(ID);

    if(iterator == m_instancedModelMap.end())
    {
        SpriteInstancedData data {event->component->sprite, new std::vector<glm::mat4>()};
        m_instancedModelMap.insert(iterator,std::make_pair(ID,data));
    }
}

void SpriteRendererSystem::OnCreate()
{
    System::OnCreate();
    EventQueue::Instance().Subscribe(this, &SpriteRendererSystem::OnSpriteInfoAdded);
}
