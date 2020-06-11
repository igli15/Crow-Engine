//
// Created by Igli milaqi on 04/04/2020.
//

#include "MeshRendererSystem.h"
#include "../Components/Transform.h"
#include "../Components/Camera.h"
#include "../Core/Game.h"
#include "../Core/Renderer.h"
#include "../Components/MeshInfo.h"

void MeshRendererSystem::OnCreate() {
    System::OnCreate();

    renderer = Game::Instance()->renderer;

    EventQueue::Instance().Subscribe(this,&MeshRendererSystem::OnMeshInfoAdded);
    EventQueue::Instance().Subscribe(this,&MeshRendererSystem::OnMeshInfoRemoved);
    EventQueue::Instance().Subscribe(this,&MeshRendererSystem::OnMeshInfoDirty);
}

void MeshRendererSystem::Init()
{
    System::Init();
    Entity cameraEntity = world->EntitiesWith<Camera>()[0];
    cameraTransform =  &world->GetComponent<Transform>(cameraEntity);
    cameraComponent = &world->GetComponent<Camera>(cameraEntity);
}

void MeshRendererSystem::Render() {
    System::Render();

    glm::mat4 camInverseMat = glm::inverse(cameraTransform->GetWorldTransform());
    glm::mat4 projection = cameraComponent->GetProjection();


    /*
    m_matIdToModelsMap.clear();

    for (auto pair: m_matricesMap)
    {
        pair.second->clear();
    }
     */

    /*
    for (const auto& entity : m_entities)
    {
        MeshInfo& meshInfo = world->GetComponent<MeshInfo>(entity);
        Transform& transform = world->GetComponent<Transform>(entity);

        m_matIdToModelsMap[meshInfo.material->ID].insert(meshInfo.model);

        int hash = Hash(meshInfo.model->ID,meshInfo.material->ID);
        auto matricesIterator = m_matricesMap.find(hash);

        if(matricesIterator == m_matricesMap.end())
        {
            std::vector<glm::mat4>* matricesVector = new std::vector<glm::mat4>();
            matricesVector->push_back(transform.GetWorldTransform());
            m_matricesMap.insert(matricesIterator, std::make_pair(hash, matricesVector));
        }
        else
        {
            matricesIterator->second->push_back(transform.GetWorldTransform());
        }

    }
*/

    for (auto pair: m_hashedMatricesMap)
    {
        pair.second->clear();
    }

    for (const auto& entity : m_entities)
    {
        MeshInfo& meshInfo = world->GetComponent<MeshInfo>(entity);
        Transform& transform = world->GetComponent<Transform>(entity);

        int hash = Hash(meshInfo.model->ID,meshInfo.material->ID);

        m_hashedMatricesMap[hash]->push_back(transform.GetWorldTransform());
    }

    for (const auto& pair:  m_matIdToModelsMap)
    {
        AbstractMaterial* material = renderer->materialMap[pair.first];

        material->GetShader()->Use();
        material->BufferShaderUniforms(camInverseMat, projection,cameraTransform->WorldPosition(), world);
        material->BufferMaterialUniforms();

        for (const auto& model : pair.second)
        {
            std::vector<glm::mat4>* modelMatricesPtr = m_hashedMatricesMap[Hash(model->ID, material->ID)];
            model->BindModelBuffer(*modelMatricesPtr);
            model->InstanceRenderMeshes(modelMatricesPtr->size());
        }
    }
}

int MeshRendererSystem::Hash(int x,int y)
{
    return  (x+y) * (x+y+1) / 2 + y;
}

void MeshRendererSystem::OnMeshInfoAdded(ComponentAddedEvent<MeshInfo>* event)
{
    event->component->owner = event->entity;
    Register(event->component);
}

void MeshRendererSystem::OnMeshInfoRemoved(ComponentRemovedEvent<MeshInfo> *event)
{
    DeRegister(event->component);
}

void MeshRendererSystem::Register(MeshInfo *meshInfo)
{
    Model* model = meshInfo->model;
    AbstractMaterial* mat = meshInfo->material;

    if(model == nullptr || mat == nullptr)
    {
        return;
    }

    m_matIdToModelsMap[mat->ID].insert(model);

    int hash = Hash(model->ID,mat->ID);

    Transform* t = world->GetComponentPtr<Transform>(meshInfo->owner);

    if(t == nullptr) throw;

    auto hashedMatricesIterator = m_hashedMatricesMap.find(hash);

    if(hashedMatricesIterator == m_hashedMatricesMap.end())
    {
        m_hashedMatricesMap.insert(hashedMatricesIterator, std::make_pair(hash, new std::vector<glm::mat4>()));
    }
}


void MeshRendererSystem::DeRegister(MeshInfo meshInfo)
{
    Model* model = meshInfo.model;
    AbstractMaterial* mat = meshInfo.material;

    if(model == nullptr || mat == nullptr)
    {
        return;
    }

    auto modelSet = m_matIdToModelsMap[mat->ID];
    auto modelIterator = modelSet.find(model);

    if(modelIterator != modelSet.end())
    {
        modelSet.erase(modelIterator);
    }
}

void MeshRendererSystem::OnMeshInfoDirty(MeshInfoDirtyEvent* event)
{
    DeRegister(*event->meshInfo);
    Register(event->meshInfo);
}
