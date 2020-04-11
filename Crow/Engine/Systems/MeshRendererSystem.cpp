//
// Created by Igli milaqi on 04/04/2020.
//

#include "MeshRendererSystem.h"
#include "../Components/Transform.h"
#include "../Components/Camera.h"



void MeshRendererSystem::OnCreate() {
    System::OnCreate();

    EventQueue::Instance().Subscribe(this, &MeshRendererSystem::OnMeshInfoAdded);
}

void MeshRendererSystem::Render() {
    System::Render();


    for (auto pair: m_instancedModelMap)
    {
        pair.second.modelMatrices->clear();
    }

    for (const auto& entity : m_entities)
    {
        MeshInfo& meshInfo = world->GetComponent<MeshInfo>(entity);
        Transform& transform = world->GetComponent<Transform>(entity);

        m_instancedModelMap[meshInfo.model->ID].modelMatrices->push_back(transform.GetWorldTransform());
    }

    for (auto pair: m_instancedModelMap)
    {
        //Buffer the all model matrices VBO to the shader
        pair.second.model->BindModelBuffer(*pair.second.modelMatrices);
        //Draw in one call all the models
        pair.second.model->InstanceRenderMeshes(pair.second.modelMatrices->size());
    }

}

void MeshRendererSystem::OnMeshInfoAdded(ComponentAddedEvent<MeshInfo> *event)
{
    event->component->model->InstanceBufferMeshes();

    int ID = event->component->model->ID;
    auto iterator = m_instancedModelMap.find(ID);

    if(iterator == m_instancedModelMap.end())
    {
        MeshInstancedData data {event->component->model, new std::vector<glm::mat4>()};
        m_instancedModelMap.insert(iterator,std::make_pair(ID,data));
    }
}
