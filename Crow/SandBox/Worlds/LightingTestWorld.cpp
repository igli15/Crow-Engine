//
// Created by Igli milaqi on 17/03/2020.
//

#include "LightingTestWorld.h"
#include "../../Engine/Core/Game.h"
#include "../../Engine/Rendering/Model.h"
#include "../Systems/RotateSystem.h"
#include "../../Engine/Rendering/Materials/ColorMaterial.h"
#include "../Components/RotateComponent.h"
#include "../../Engine/Core/ResourceManager.h"
#include "../../Engine/Components/Transform.h"
#include "../../Engine/Feather/EntityHandle.h"
#include "../../Engine/Components/MeshInfo.h"
#include "../../Engine/Components/Light.h"

void LightingTestWorld::Build()
{
    World::Build();

    Game::Instance()->resourceManager->CreateShader("VertexShader.vs","FragmentShader.fs","unlitShader");

    //Load the models
    Model* cube = Game::Instance()->resourceManager->LoadModel((MODEL_PATH + "cube.obj"),"cube");
    Model* gunModel = Game::Instance()->resourceManager->LoadModel((MODEL_PATH + "pistol.obj"),"gunModel");

    RegisterSystem<RotateSystem>();
    SetSystemSignature<RotateSystem,Transform,RotateComponent>();

    ColorMaterial* mat = new ColorMaterial("unlitShader");

    cameraEntity->GetComponent<Transform>().component->Translate(glm::vec3(0,0,5));

    EntityHandle gunEntity = CreateEntity();

    gunEntity.AddComponent(Transform{});
    Transform *t2 = gunEntity.GetComponent<Transform>().component;
    t2->Scale(glm::vec3(0.1f, 0.1f, 0.1f));

    MeshInfo gunMeshInfo{};
    gunMeshInfo.model = gunModel;

    //mat->mainColor = glm::vec3(0.75164f,0.60648f,0.22648f);
    //mat->specularColor = glm::vec3(0.628281f,0.555802,0.366065);

    mat->mainColor = glm::vec3(1);
    mat->specularColor = glm::vec3(1);
    mat->shininess = 0.4f;

    gunMeshInfo.material = mat;
    gunEntity.AddComponent(gunMeshInfo);
    gunEntity.AddComponent(RotateComponent{1});


    EntityHandle cubeEntity = CreateEntity();
    cubeEntity.AddComponent(Transform{});
    Transform *cubeTransform = cubeEntity.GetComponent<Transform>().component;
    cubeTransform->Scale(glm::vec3(0.5f, 0.5f, 0.5f));
    cubeTransform->Translate(glm::vec3(-6,0,0));
    cubeTransform->Rotate(45,glm::vec3(1,0,0));

    MeshInfo cubeMeshInfo{};
    cubeMeshInfo.model = cube;
    cubeMeshInfo.material = mat;
    cubeEntity.AddComponent(cubeMeshInfo);


    EntityHandle pointLightEntity = CreateEntity();
    auto t3 = pointLightEntity.AddComponent(Transform{});
    t3->Rotate(45,glm::vec3(1,0,0));
    t3->Translate(glm::vec3(-2,0,0));
    Light* pointLight = pointLightEntity.AddComponent(Light{});
    pointLight->color = glm::vec3(0,1,0);
    pointLight->type = Light::POINT;


    EntityHandle lightEntity = CreateEntity();
    auto t = lightEntity.AddComponent(Transform{});
    t->Rotate(-45,glm::vec3(1,0,0));
    lightEntity.AddComponent(Light{glm::vec3(1,0,0)});

    EntityHandle spotLightEntity = CreateEntity();
    Transform* spotTransform = spotLightEntity.AddComponent(Transform{});
    spotTransform->Translate(glm::vec3(0,0,-5));
    spotTransform->Rotate(180,glm::vec3(0,1,0));
    Light* spotLight = spotLightEntity.AddComponent(Light{});
    spotLight->color = glm::vec3(0,1,1);
    spotLight->type = Light::SPOT;


}
