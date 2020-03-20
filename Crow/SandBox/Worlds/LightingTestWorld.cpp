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

    Game::Instance()->resourceManager->CreateShader("VertexShader.vs","FragmentShader.fs","litShader");

    //Load the models
    Model* cube = Game::Instance()->resourceManager->LoadModel((MODEL_PATH + "shape.obj"),"cube");
    Model* gunModel = Game::Instance()->resourceManager->LoadModel((MODEL_PATH + "pistol.obj"),"gunModel");

    Model* planeModel = Game::Instance()->resourceManager->LoadModel((MODEL_PATH + "plane.obj"),"plane");

    RegisterSystem<RotateSystem>();
    SetSystemSignature<RotateSystem,Transform,RotateComponent>();

    ColorMaterial* mat = new ColorMaterial("litShader");
    mat->mainColor = glm::vec3(0.7,0.7,0.7);
    mat->specularColor = glm::vec3(1);
    mat->shininess = 16;

    ColorMaterial* redMat = new ColorMaterial("litShader");
    redMat->mainColor = glm::vec3(glm::vec3(1,1,1));
    redMat->specularColor = glm::vec3(1,0,0);
    redMat->shininess = 2;

    Transform* camTransform = cameraEntity->GetComponent<Transform>().component;
    camTransform->Translate(glm::vec3(0,4,6));
    camTransform->Rotate(-45,glm::vec3(1,0,0));

    EntityHandle plane = CreateEntity();
    Transform* planeTransform = plane.AddComponent(Transform{});
    plane.AddComponent(MeshInfo{planeModel,mat});
    planeTransform->Translate(glm::vec3(0,-2,0));
    planeTransform->Scale(glm::vec3(20,10,10));


    EntityHandle cubeEntity = CreateEntity();
    cubeEntity.AddComponent(Transform{});
    Transform *cubeTransform = cubeEntity.GetComponent<Transform>().component;
    cubeEntity.AddComponent(RotateComponent{1});

    MeshInfo cubeMeshInfo{};
    cubeMeshInfo.model = cube;
    cubeMeshInfo.material = redMat;
    cubeEntity.AddComponent(cubeMeshInfo);


    EntityHandle lightEntity = CreateEntity();
    auto dirLightTransform = lightEntity.AddComponent(Transform{});
    dirLightTransform->Rotate(-45,glm::vec3(1,0,0));
    Light* dirLight = lightEntity.AddComponent(Light{glm::vec3(0.8,0.8,0.8)});
    dirLight->intensity = 0.5;

    EntityHandle pointLightEntity = CreateEntity();
    auto pointLightTransform = pointLightEntity.AddComponent(Transform{});
    pointLightTransform->Translate(glm::vec3(-4,0,0));
    Light* pointLight = pointLightEntity.AddComponent(Light{glm::vec3(0,0,0.8)});
    pointLight->type = pointLight->POINT;

    EntityHandle pointLightEntity2 = CreateEntity();
    auto pointLightTransform2 = pointLightEntity2.AddComponent(Transform{});
    pointLightTransform2->Translate(glm::vec3(4,0,0));
    Light* pointLight2 = pointLightEntity2.AddComponent(Light{glm::vec3(0,0,0.8)});
    pointLight2->type = pointLight->POINT;


    EntityHandle spotLightEntity = CreateEntity();
    auto spotLightTransform = spotLightEntity.AddComponent(Transform{});
    spotLightTransform->Translate(glm::vec3(0,2,0));
    spotLightTransform->Rotate(-90,glm::vec3(1,0,0));
    Light* spotLight = spotLightEntity.AddComponent(Light{glm::vec3(0.5,0.5,0)});
    spotLight->type = pointLight->SPOT;
}
