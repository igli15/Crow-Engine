//
// Created by Igli milaqi on 04/04/2020.
//

#include "MeshRendererSystem.h"
#include "../Components/Transform.h"
#include "../Components/Camera.h"
#include "../Core/Game.h"
#include "../Core/Renderer.h"


void MeshRendererSystem::OnCreate() {
    System::OnCreate();

    renderer = Game::Instance()->renderer;
}

void MeshRendererSystem::Render() {
    System::Render();

    Entity cameraEntity = world->EntitiesWith<Camera>()[0];
    Transform& cameraTransform = world->GetComponent<Transform>(cameraEntity);
    Camera& camera=  world->GetComponent<Camera>(cameraEntity);

    glm::mat4 camInverseMat = glm::inverse(cameraTransform.GetWorldTransform());
    glm::mat4 projection = camera.GetProjection();


    for (auto pair: m_matIdToModelsMap)
    {
        pair.second.clear();
    }

    for (auto pair: m_modelIDtoMatricesMap)
    {
        pair.second->clear();
    }

    for (const auto& entity : m_entities)
    {
        MeshInfo& meshInfo = world->GetComponent<MeshInfo>(entity);
        Transform& transform = world->GetComponent<Transform>(entity);

        m_matIdToModelsMap[meshInfo.material->ID].insert(meshInfo.model);

        auto matricesIterator = m_modelIDtoMatricesMap.find(meshInfo.model->ID);

        if(matricesIterator == m_modelIDtoMatricesMap.end())
        {
            std::vector<glm::mat4>* matricesVector = new std::vector<glm::mat4>();
            matricesVector->push_back(transform.GetWorldTransform());
            m_modelIDtoMatricesMap.insert(matricesIterator,std::make_pair(meshInfo.model->ID,matricesVector));
        }
        else
        {
            matricesIterator->second->push_back(transform.GetWorldTransform());
        }

    }

    for (const auto& pair:  m_matIdToModelsMap)
    {
        AbstractMaterial* material = renderer->materialMap[pair.first];

        material->GetShader()->Use();
        material->BufferShaderUniforms(camInverseMat, projection,cameraTransform.WorldPosition(), world);
        material->BufferMaterialUniforms();

        for (const auto& model : pair.second)
        {
            std::vector<glm::mat4>* modelMatricesPtr = m_modelIDtoMatricesMap[model->ID];
            model->BindModelBuffer(*modelMatricesPtr);
            model->InstanceRenderMeshes(modelMatricesPtr->size());
        }
    }
}
