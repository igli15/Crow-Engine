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

void PrototypeWorld::Build()
{
    World::Build();

    ColorMaterial* mat = new ColorMaterial("litShader");
    mat->mainColor = glm::vec3(0.7,0.7,0.7);
    mat->specularColor = glm::vec3(1);
    mat->shininess = 16;

    Model* planeModel = Game::Instance()->resourceManager->GetModel("plane");

    ComponentHandle<Transform> cameraTransform = cameraEntity->GetComponent<Transform>();
    cameraTransform.component->Translate(glm::vec3(0,4,6));
    cameraTransform.component->Rotate(-45,glm::vec3(1,0,0));

    EntityHandle planeEntity = CreateEntity();
    Transform* planeTransform = planeEntity.AddComponent(Transform{});
    planeTransform->SetScale(glm::vec3(20,10,10));
    planeEntity.AddComponent(MeshInfo{planeModel,mat});

    EntityHandle lightEntity = CreateEntity();
    auto dirLightTransform = lightEntity.AddComponent(Transform{});
    dirLightTransform->Rotate(-45,glm::vec3(1,0,0));
    Light* dirLight = lightEntity.AddComponent(Light{glm::vec3(0.8,0.8,0.8)});
    dirLight->intensity = 1;

}
