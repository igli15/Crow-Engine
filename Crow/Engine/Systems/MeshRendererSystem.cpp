//
// Created by Igli milaqi on 15/03/2020.
//

#include "MeshRendererSystem.h"
#include "../Feather/World.h"
#include "../Components/Transform.h"
#include "../Components/MeshInfo.h"
#include "../Feather/EntityHandle.h"
#include "../Components/Camera.h"

void MeshRendererSystem::Render()
{
    System::Render();

    Entity cameraEntity = world->EntitiesWith<Camera>()[0];
    Transform& cameraTransform = world->GetComponent<Transform>(cameraEntity);
    Camera& camera=  world->GetComponent<Camera>(cameraEntity);

    glm::mat4 camInverseMat = glm::inverse(cameraTransform.GetWorldTransform());

    for (auto const& entity : m_entities)
    {
        Transform& transform = world->GetComponent<Transform>(entity);
        MeshInfo& meshInfo = world->GetComponent<MeshInfo>(entity);

        if(meshInfo.model == nullptr || meshInfo.material == nullptr)
        {
            ENGINE_LOG_ERROR("Trying to draw mesh without a material or model");
            continue;
        }

        meshInfo.material->BufferUniforms(transform.GetWorldTransform(), camInverseMat, camera.GetProjection(),
                                          cameraTransform.WorldPosition(), world);

        meshInfo.model->Draw();
    }

}

void MeshRendererSystem::Init()
{
    System::Init();
}

