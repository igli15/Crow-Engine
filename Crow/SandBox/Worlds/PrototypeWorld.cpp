//
// Created by Igli milaqi on 29/03/2020.
//

#include "PrototypeWorld.h"

#include "../../Engine/Core/Game.h"
#include "../../Engine/Rendering/Model.h"
#include "../../Engine/Rendering/Materials/ColorMaterial.h"
#include "../../Engine/Core/ResourceManager.h"
#include "../../Engine/Components/Transform.h"
#include "../../Engine/Feather/EntityHandle.h"
#include "../../Engine/Components/MeshInfo.h"
#include "../../Engine/Components/Light.h"
#include "../../Engine/Components/SphereCollider.h"
#include "../../Engine/Components/Camera.h"
#include "../../Engine/Rendering/Materials/TranslucentColorMat.h"
#include "../Components/MoveComponent.h"
#include "../Systems/MoveSystem.h"


void PrototypeWorld::Build()
{
    World::Build();

    RegisterSystem<MoveSystem>();

    Model* planeModel = Game::Instance()->resourceManager->GetModel("plane");
    Model* lanternModel = Game::Instance()->resourceManager->GetModel("lantern");
    Model* graveModel = Game::Instance()->resourceManager->GetModel("gravestone");
    Model* ghostModel = Game::Instance()->resourceManager->GetModel("ghost");

    ColorMaterial* mat = new ColorMaterial();
    mat->mainColor = glm::vec3(0.7,0.7,0.7);
    mat->specularColor = glm::vec3(1);
    mat->shininess = 16;

    TranslucentColorMat* lanternMaterial = new TranslucentColorMat();
    lanternMaterial->ambientIntensity = 0.5;

    TranslucentColorMat* ghostMaterial = new TranslucentColorMat();
    ghostMaterial->translucentScale = 2;
    ghostMaterial->translucentDistortion = 1;
    ghostMaterial->translucentPower = 0.5;

    EntityHandle cameraEntity = CreateEntity();
    cameraEntity.AddComponent(Camera{});
    Transform* cameraTransform = cameraEntity.AddComponent(Transform{});
    cameraTransform->Translate(glm::vec3(0,6,5));
    cameraTransform->Rotate(-50,glm::vec3(1,0,0));

    EntityHandle planeEntity = CreateEntity();
    Transform* planeTransform = planeEntity.AddComponent(Transform{});
    planeTransform->SetScale(glm::vec3(20,10,10));
    planeEntity.AddComponent(MeshInfo{planeModel,mat});


    {
        EntityHandle lanternEntity = CreateEntity();
        Transform *lanternTransform = lanternEntity.AddComponent(Transform{});
        lanternTransform->Translate(glm::vec3(0, 1, -1.5));
        lanternTransform->Scale(glm::vec3(0.5f,0.5f,0.5f));
        //lanternTransform->Rotate(135,glm::vec3(1,0,0));
        lanternEntity.AddComponent(MeshInfo{lanternModel, lanternMaterial});
        Light *lanternLight = lanternEntity.AddComponent(Light{});
        lanternLight->type = Light::POINT;
        lanternLight->quadratic = 0.3f;
    }

    {
        EntityHandle lanternEntity = CreateEntity();
        Transform *lanternTransform = lanternEntity.AddComponent(Transform{});
        lanternTransform->Translate(glm::vec3(6, 1, -2));
        lanternTransform->Scale(glm::vec3(0.5f,0.5f,0.5f));
        //lanternTransform->Rotate(135,glm::vec3(1,0,0));
        lanternEntity.AddComponent(MeshInfo{lanternModel, lanternMaterial});
        Light *lanternLight = lanternEntity.AddComponent(Light{});
        lanternLight->type = Light::POINT;
        lanternLight->quadratic = 0.3f;
    }

    {
        EntityHandle lanternEntity = CreateEntity();
        Transform *lanternTransform = lanternEntity.AddComponent(Transform{});
        lanternTransform->Translate(glm::vec3(-6, 1, -2));
        lanternTransform->Scale(glm::vec3(0.5f,0.5f,0.5f));
        //lanternTransform->Rotate(135,glm::vec3(1,0,0));
        lanternEntity.AddComponent(MeshInfo{lanternModel, lanternMaterial});
        Light *lanternLight = lanternEntity.AddComponent(Light{});
        lanternLight->type = Light::POINT;
        lanternLight->quadratic = 0.3f;
    }


    for (int i = 0; i < 3; ++i)
    {
        EntityHandle ghost1 = CreateEntity();
        Transform *ghost1Transform = ghost1.AddComponent(Transform{});
        ghost1Transform->Translate(glm::vec3(-5, 1, 0.5 * i));
        ghost1Transform->Scale(glm::vec3(0.1, 0.1, 0.1));
        ghost1Transform->Rotate(90, glm::vec3(0, 1, 0));
        ghost1.AddComponent(MeshInfo{ghostModel, ghostMaterial});
        ghost1.AddComponent(MoveComponent{glm::vec3(0,0,1),0.05f * (i+1)});
    }

    for (int i = 0; i < 3; ++i)
    {
        EntityHandle ghost1 = CreateEntity();
        Transform *ghost1Transform = ghost1.AddComponent(Transform{});
        ghost1Transform->Translate(glm::vec3(5, 1, 0.5 * i));
        ghost1Transform->Scale(glm::vec3(0.1, 0.1, 0.1));
        ghost1Transform->Rotate(-90, glm::vec3(0, 1, 0));
        ghost1.AddComponent(MeshInfo{ghostModel, ghostMaterial});
        ghost1.AddComponent(MoveComponent{glm::vec3(0,0,1),0.05f * (i+1)});
    }


}
