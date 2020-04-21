//
// Created by Igli milaqi on 21/04/2020.
//

#include "MovementTestWorld.h"
#include "../../Engine/Rendering/Model.h"
#include "../../Engine/Core/ResourceManager.h"
#include "../../Engine/Core/Game.h"
#include "../../Engine/Rendering/Materials/ColorMaterial.h"
#include "../../Engine/Components/Transform.h"
#include "../../Engine/Components/Camera.h"
#include "../../Engine/Feather/EntityHandle.h"
#include "../../Engine/Components/Light.h"
#include "../../Engine/Components/RigidBody.h"
#include "../Components/MoveComponent.h"
#include "../Systems/MoveSystem.h"

void MovementTestWorld::Build()
{
    World::Build();

    RegisterSystem<MoveSystem>();

    ResourceManager* resourceManager = Game::Instance()->resourceManager;

    Model* cubeModel = resourceManager->GetModel("cube");
    ColorMaterial* material = resourceManager->GetMaterial<ColorMaterial>("defaultMat");


    EntityHandle cameraEntity = CreateEntity();
    cameraEntity.AddComponent(Camera{});
    Transform* camTransform = cameraEntity.AddComponent(Transform{});
    camTransform->Translate(glm::vec3(0,4,5));
    camTransform->Rotate(-45,glm::vec3(1,0,0));



    EntityHandle cubeEntity = CreateEntity();
    cubeEntity.AddComponent(Transform{});
    Transform *cubeTransform = cubeEntity.GetComponent<Transform>().component;
    MeshInfo cubeMeshInfo{};
    cubeMeshInfo.model = cubeModel;
    cubeMeshInfo.material = material;
    cubeEntity.AddComponent(cubeMeshInfo);
    cubeEntity.AddComponent(RigidBody{glm::vec3(0),glm::vec3(1)});
    cubeEntity.AddComponent(MoveComponent{0.002f});


    EntityHandle lightEntity = CreateEntity();
    auto dirLightTransform = lightEntity.AddComponent(Transform{});
    dirLightTransform->Rotate(45,glm::vec3(1,0,0));
    Light* dirLight = lightEntity.AddComponent(Light{glm::vec3(0.8,0.8,0.8)});
    dirLight->intensity = 1;
    dirLight->type = dirLight->DIRECTIONAL;


}
