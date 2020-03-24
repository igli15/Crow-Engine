//
// Created by Igli milaqi on 24/03/2020.
//

#include "PhysicsTestWorld.h"

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

void PhysicsTestWorld::Build()
{
    World::Build();

    Game::Instance()->resourceManager->CreateShader("VertexShader.vs","FragmentShader.fs","litShader");

    Model* planeModel = Game::Instance()->resourceManager->LoadModel((MODEL_PATH + "plane.obj"),"plane");

    ColorMaterial* mat = new ColorMaterial("litShader");
    mat->mainColor = glm::vec3(0.7,0.7,0.7);
    mat->specularColor = glm::vec3(1);
    mat->shininess = 16;

    Transform* camTransform = cameraEntity->GetComponent<Transform>().component;
    camTransform->Translate(glm::vec3(0,4,6));
    camTransform->Rotate(-45,glm::vec3(1,0,0));

    EntityHandle plane = CreateEntity();
    Transform* planeTransform = plane.AddComponent(Transform{});
    plane.AddComponent(MeshInfo{planeModel,mat});
    planeTransform->Translate(glm::vec3(0,-2,0));
    planeTransform->Scale(glm::vec3(20,10,10));

    EntityHandle lightEntity = CreateEntity();
    auto dirLightTransform = lightEntity.AddComponent(Transform{});
    dirLightTransform->Rotate(-45,glm::vec3(1,0,0));
    Light* dirLight = lightEntity.AddComponent(Light{glm::vec3(0.8,0.8,0.8)});
    dirLight->intensity = 1;

}
