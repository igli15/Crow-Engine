//
// Created by Igli milaqi on 15/03/2020.
//

#include "MeshRendererSystem.h"
#include "../Feather/World.h"
#include "../Components/Transform.h"
#include "../Components/MeshInfo.h"

void MeshRendererSystem::Render()
{
    System::Render();

    for (auto const& entity : m_entities)
    {
        Transform& transform = world->GetComponent<Transform>(entity);
        MeshInfo& meshInfo = world->GetComponent<MeshInfo>(entity);

        if(meshInfo.model == nullptr || meshInfo.material == nullptr)
        {
            ENGINE_LOG_ERROR("Trying to draw mesh without a material or model");
            continue;
        }


        //meshInfo.material->Render(meshInfo.model,transform.GetLocalTransform(),)
    }
}
