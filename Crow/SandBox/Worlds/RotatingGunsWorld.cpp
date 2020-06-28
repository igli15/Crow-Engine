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
#include "../../Engine/Systems/TextRenderingSystem.h"
#include "../../Engine/Systems/TransformHierarchySystem.h"
#include "../../Engine/Utils/Random.h"
#include "../../Game/Systems/DebugTextSystem.h"
#include "../../Game/Components/DebugTextComponent.h"

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
    RegisterSystem<MeshRendererSystem>();
    RegisterSystem<TransformHierarchySystem>();
    RegisterSystem<TextRenderingSystem>();
    SetSystemSignature<MeshRendererSystem,Transform,MeshInfo>();
    RegisterSystem<DebugTextSystem>();

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
            MeshInfo gunMeshInfo{gunModel,mat};
            mat->mainColor = glm::vec3(0.8f,0.8f,0.8f);
            gunEntity.AddComponent(gunMeshInfo);
            gunEntity.AddComponent(RotateComponent{glm::vec3(0,1,0),Random::RandomRange(400.0f,500.0f)});
            //gunEntity.AddComponent(SphereCollider{1});
        }
    }


    EntityHandle textEntity = CreateEntity();
    Transform* textTransform = textEntity.AddComponent(Transform{});
    textTransform->SetLocalPosition(glm::vec3(Game::Instance()->screenData.screenWidth - 200,Game::Instance()->screenData.screenHeight - 50,0));
    Text* fpsText =  textEntity.AddComponent(Text{"FPS:",glm::vec3(1),0.5f,Game::Instance()->resourceManager->GetFont("roboto")});

    textEntity.AddComponent(DebugTextComponent{fpsText,nullptr});

    EntityHandle lightEntity = CreateEntity();
    auto dirLightTransform = lightEntity.AddComponent(Transform{});
    dirLightTransform->Rotate(-45,glm::vec3(1,0,0));
    Light* dirLight = lightEntity.AddComponent(Light{glm::vec3(0.8,0.8,0.8)});
    dirLight->intensity = 1;

}
