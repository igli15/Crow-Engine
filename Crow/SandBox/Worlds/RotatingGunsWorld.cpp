//
// Created by Igli milaqi on 06/03/2020.
//

#include "RotatingGunsWorld.h"


#include "../../Engine/Components/Transform.h"
#include "../../Engine/Systems/MeshRendererSystem.h"
#include "../../Engine/Components/MeshInfo.h"
#include "../../Engine/Core/Game.h"
#include "../../Engine/Core/ResourceManager.h"
#include "../../Engine/Rendering/Materials/ColorMaterial.h"
#include "../Systems/RotateSystem.h"
#include "../Components/RotateComponent.h"
#include "../../Engine/Feather/EntityHandle.h"

void RotatingGunsWorld::Build()
{
    World::Build();

    //Register the shader once
    Game::Instance()->resourceManager->CreateShader("VertexShader.vs","FragmentShader.fs","unlitShader");

    //Load the models
    Model* gunModel = Game::Instance()->resourceManager->LoadModel((MODEL_PATH + "pistol.obj"),"gunModel");

    RegisterSystem<RotateSystem>();
    SetSystemSignature<RotateSystem,Transform,RotateComponent>();

    ColorMaterial* mat = new ColorMaterial("unlitShader");

    cameraEntity->GetComponent<Transform>().component->Translate(glm::vec3(50,50,100));
    for (int i = 0; i < 100; ++i)
    {
        for (int j = 0; j < 100; ++j)
        {
            EntityHandle gunEntity = CreateEntity();

            gunEntity.AddComponent(Transform{});
            Transform *t2 = gunEntity.GetComponent<Transform>().component;
            t2->Translate(glm::vec3(i , j, -10));
            t2->Scale(glm::vec3(0.05f, 0.05f, 0.05f));
            t2->Rotate(-25, glm::vec3(0, 1, 0));

            MeshInfo gunMeshInfo{};
            gunMeshInfo.model = gunModel;
            mat->mainColor = glm::vec3(0.8f,0.8f,0.8f);
            gunMeshInfo.material = mat;
            gunEntity.AddComponent(gunMeshInfo);
            gunEntity.AddComponent(RotateComponent{5});
        }
    }
    //ENGINE_LOG("Here");

}
