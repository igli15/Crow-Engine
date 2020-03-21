//
// Created by Igli milaqi on 21/03/2020.
//

#include "TranslucentMaterialTestWorld.h"
#include "../Systems/RotateSystem.h"
#include "../../Engine/Rendering/Materials/ColorMaterial.h"
#include "../../Engine/Rendering/Model.h"
#include "../../Engine/Core/Game.h"
#include "../../Engine/Components/Transform.h"
#include "../Components/RotateComponent.h"
#include "../../Engine/Core/ResourceManager.h"
#include "../../Engine/Feather/EntityHandle.h"
#include "../../Engine/Components/MeshInfo.h"
#include "../../Engine/Components/Light.h"
#include "../../Engine/Rendering/Materials/TranslucentColorMat.h"

void TranslucentMaterialTestWorld::Build()
{
    World::Build();

    Game::Instance()->resourceManager->CreateShader("VertexShader.vs","FragmentShader.fs","litShader");
    Game::Instance()->resourceManager->CreateShader("TranslucentVertexShader.vs","TranslucentFragmentShader.fs","translucentShader");

    //Load the models
    Model* dragon = Game::Instance()->resourceManager->LoadModel((MODEL_PATH + "dragon.obj"),"dragon");
    Model* planeModel = Game::Instance()->resourceManager->LoadModel((MODEL_PATH + "plane.obj"),"plane");

    RegisterSystem<RotateSystem>();
    SetSystemSignature<RotateSystem,Transform,RotateComponent>();

    TranslucentColorMat* translucentMat = new TranslucentColorMat();
    translucentMat->translucentScale = 1;
    translucentMat->translucentColor = glm::vec3(1,0.8,0.6);
    translucentMat->shininess = 256;

    ColorMaterial* mat = new ColorMaterial("litShader");
    mat->mainColor = glm::vec3(0.7,0.7,0.7);
    mat->specularColor = glm::vec3(1);
    mat->shininess = 16;

    Transform* camTransform = cameraEntity->GetComponent<Transform>().component;
    camTransform->Translate(glm::vec3(0,4,5));
    camTransform->Rotate(-45,glm::vec3(1,0,0));

    EntityHandle plane = CreateEntity();
    Transform* planeTransform = plane.AddComponent(Transform{});
    plane.AddComponent(MeshInfo{planeModel,mat});
    planeTransform->Translate(glm::vec3(0,-2,0));
    planeTransform->Scale(glm::vec3(20,10,10));


    EntityHandle cubeEntity = CreateEntity();
    cubeEntity.AddComponent(Transform{});
    Transform *cubeTransform = cubeEntity.GetComponent<Transform>().component;
    cubeTransform->Scale(glm::vec3(3,3,3));
    cubeEntity.AddComponent(RotateComponent{1});

    MeshInfo cubeMeshInfo{};
    cubeMeshInfo.model = dragon;
    cubeMeshInfo.material = translucentMat;
    cubeEntity.AddComponent(cubeMeshInfo);


    EntityHandle lightEntity = CreateEntity();
    auto dirLightTransform = lightEntity.AddComponent(Transform{});
    dirLightTransform->Rotate(135,glm::vec3(1,0,0));
    Light* dirLight = lightEntity.AddComponent(Light{glm::vec3(0.8,0.8,0.8)});
    dirLight->intensity = 1;

    EntityHandle lightEntity2 = CreateEntity();
    auto dirLightTransform2 = lightEntity2.AddComponent(Transform{});
    dirLightTransform2->Rotate(-45,glm::vec3(1,0,0));
    Light* dirLight2 = lightEntity2.AddComponent(Light{glm::vec3(1,1,1)});
    dirLight2->intensity = 0.8;


}
