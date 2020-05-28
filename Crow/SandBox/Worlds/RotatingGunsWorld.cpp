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
#include "../../Game/Systems/RotateSystem.h"
#include "../../Game/Components/RotateComponent.h"
#include "../../Engine/Feather/EntityHandle.h"
#include "../../Engine/Components/SphereCollider.h"
#include "../../Engine/Components/Camera.h"
#include "../../Engine/Components/Text.h"
#include "../../Engine/Components/Light.h"
#include "../../Engine/Rendering/Materials/ColorMaterial.h"
#include "../../Engine/Components/SpriteInfo.h"
#include "../../Engine/Rendering/Materials/UnlitMaterial.h"

void RotatingGunsWorld::Build()
{
    World::Build();

    //Register the shader once
    //Game::Instance()->resourceManager->CreateShader("VertexShader.vs","FragmentShader.fs","instancedLitShader");
    //Game::Instance()->resourceManager->CreateShader("VertexShader.vs","FragmentShader.fs","litShader");


    //Load the models
    Model* gunModel = Game::Instance()->resourceManager->LoadModel(("pistol.obj"),"gunModel");

    RegisterSystem<RotateSystem>();
    SetSystemSignature<RotateSystem,Transform,RotateComponent>();

    //ColorMaterial* mat = new ColorMaterial();
    UnlitMaterial* mat = Game::Instance()->resourceManager->GetMaterial<UnlitMaterial>("whiteUnlitMat");

    EntityHandle cameraEntity = CreateEntity();
    cameraEntity.AddComponent(Camera{});
    cameraEntity.AddComponent(Transform{})->Translate(glm::vec3(50,50,60));
    //cameraEntity->GetComponent<Transform>().component->Translate(glm::vec3(50,50,100));
    for (int i = 0; i < 100; ++i)
    {
        for (int j = 0; j < 100; ++j)
        {
            EntityHandle gunEntity = CreateEntity();

            gunEntity.AddComponent(Transform{});
            Transform& t2 = gunEntity.GetComponent<Transform>();
            t2.Translate(glm::vec3(i , j, -10));
            t2.Scale(glm::vec3(0.05f, 0.05f, 0.05f));
            t2.Rotate(-25, glm::vec3(0, 1, 0));

            //MeshInfo gunMeshInfo{};
            MeshInfo gunMeshInfo{};
            gunMeshInfo.model = gunModel;
            mat->mainColor = glm::vec3(0.8f,0.8f,0.8f);
            gunMeshInfo.material = mat;
            gunEntity.AddComponent(gunMeshInfo);
            gunEntity.AddComponent(RotateComponent{glm::vec3(0,1,0),5});
            //gunEntity.AddComponent(SphereCollider{1});
        }
    }

    EntityHandle textEntity = CreateEntity();
    Transform* textTransform = textEntity.AddComponent(Transform{});
    textTransform->SetLocalPosition(glm::vec3(0,0,0));
    textEntity.AddComponent(Text{"Hello Text",glm::vec3(1,0,0),1,Game::Instance()->resourceManager->GetFont("roboto")});

    EntityHandle lightEntity = CreateEntity();
    auto dirLightTransform = lightEntity.AddComponent(Transform{});
    dirLightTransform->Rotate(-45,glm::vec3(1,0,0));
    Light* dirLight = lightEntity.AddComponent(Light{glm::vec3(0.8,0.8,0.8)});
    dirLight->intensity = 1;

}
