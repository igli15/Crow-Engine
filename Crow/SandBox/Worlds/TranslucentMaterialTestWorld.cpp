//
// Created by Igli milaqi on 21/03/2020.
//

#include "TranslucentMaterialTestWorld.h"
#include "../../Game/Systems/RotateSystem.h"
#include "../../Engine/Rendering/Materials/ColorMaterial.h"
#include "../../Engine/Rendering/Model.h"
#include "../../Engine/Core/Game.h"
#include "../../Engine/Components/Transform.h"
#include "../../Game/Components/RotateComponent.h"
#include "../../Engine/Core/ResourceManager.h"
#include "../../Engine/Feather/EntityHandle.h"
#include "../../Engine/Components/MeshInfo.h"
#include "../../Engine/Components/Light.h"
#include "../../Engine/Rendering/Materials/TranslucentColorMat.h"
#include "../../Engine/Components/Camera.h"
#include "../../Engine/Rendering/Materials/TextureMaterial.h"
#include "../../Engine/Rendering/Materials/WaterMaterial.h"
#include "../../Engine/Rendering/Materials/PortalMaterial.h"
#include "../../Engine/Systems/MeshRendererSystem.h"
#include "../../Engine/Systems/TransformHierarchySystem.h"
#include "../../Engine/Systems/CollisionDetectionSystem.h"
#include "../../Engine/Systems/TextRenderingSystem.h"
#include "../../Engine/Systems/SpriteRendererSystem.h"

void TranslucentMaterialTestWorld::Build()
{
    World::Build();


    ResourceManager* resourceManager = Game::Instance()->resourceManager;

    RegisterSystem<MeshRendererSystem>();
    RegisterSystem<CollisionDetectionSystem>();
    RegisterSystem<TransformHierarchySystem>();
    RegisterSystem<TextRenderingSystem>();
    RegisterSystem<SpriteRendererSystem>();
    SetSystemSignature<MeshRendererSystem,Transform,MeshInfo>();

    //Load the models
    Model* dragon = resourceManager->GetModel("dragon");
    Model* planeModel = resourceManager->GetModel("plane");
    Model* cubeModel = resourceManager->GetModel("cube");

    RegisterSystem<RotateSystem>();
    SetSystemSignature<RotateSystem,Transform,RotateComponent>();

    TranslucentColorMat* translucentMat = resourceManager->CreateMaterial<TranslucentColorMat>("translucentDragonMat");
    translucentMat->translucentScale = 1;
    translucentMat->translucentColor = glm::vec3(1,1,1);
    translucentMat->shininess = 16;

    TranslucentColorMat* translucentMat2 = resourceManager->CreateMaterial<TranslucentColorMat>("translucentDragonMat2");
    translucentMat2->translucentScale = 1;
    translucentMat2->translucentColor = glm::vec3(1,0,1);
    translucentMat2->shininess = 16;

    WaterMaterial* mat = resourceManager->GetMaterial<WaterMaterial>("waterMaterial");
    //mat->mainColor = glm::vec3(0.425, 0.807, 0.971);
    mat->mainColor = glm::vec3(0.18, 0.32, 0.45);

    mat->waveNoiseTexture = resourceManager->GetTexture("perlinNoise");
    mat->depthGradientTexture = resourceManager->GetTexture("gradientMap");
    mat->foamGradientTexture= resourceManager->GetTexture("foamGradient");
    mat->causticsTexture = resourceManager->GetTexture("causticsTexture");


    TextureMaterial* textureMaterial = resourceManager->CreateMaterial<TextureMaterial>("containerMat");
    Texture* containerDiffuse = resourceManager->GetTexture("containerDiffuse");
    Texture* containerSpecular = resourceManager->GetTexture("containerSpecular");
    Texture* emission = resourceManager->GetTexture("matrixTexture");
    textureMaterial->diffuseTexture = containerDiffuse;
    textureMaterial->specularTexture = containerSpecular;
    textureMaterial->emissionTexture = emission;
    textureMaterial->shininess = 128;
    textureMaterial->emissionScale = 3;

    EntityHandle cameraEntity = CreateEntity();
    cameraEntity.AddComponent(Camera{});
    Transform* camTransform = cameraEntity.AddComponent(Transform{});
    camTransform->Translate(glm::vec3(0,9,10));
    camTransform->Rotate(-60,glm::vec3(1,0,0));

    EntityHandle plane = CreateEntity();
    Transform* planeTransform = plane.AddComponent(Transform{});
    plane.AddComponent(MeshInfo{planeModel,mat});
    planeTransform->Translate(glm::vec3(0,-2,0));
    planeTransform->Scale(glm::vec3(4,1,20));

    EntityHandle portalPlane = CreateEntity();
    Transform* portalPlaneTransform = portalPlane.AddComponent(Transform{});

    PortalMaterial* portalMaterial = resourceManager->GetMaterial<PortalMaterial>("portalMaterial");
    portalMaterial->mainColor = glm::vec3(0.9f,0.7f,0.2);
    portalMaterial->secondColor = glm::vec3(0.96f,0.9f,0.255);
    portalMaterial->noiseTexture = resourceManager->GetTexture("perlinNoise");
    portalMaterial->rotationMaskTexture = resourceManager->GetTexture("portalRotationMask");
    portalMaterial->portalGlowMask = resourceManager->GetTexture("portalGlowMap");

    portalPlane.AddComponent(MeshInfo{resourceManager->GetModel("PortalPlane"),portalMaterial});
    portalPlaneTransform->Translate(glm::vec3(0,2,3));
    //portalPlaneTransform->Rotate(90,glm::vec3(0,0,1));


    EntityHandle lightEntity = CreateEntity();
    auto dirLightTransform = lightEntity.AddComponent(Transform{});
    //dirLightTransform->Rotate(-45,glm::vec3(1,0,0));
    //dirLightTransform->Translate(glm::vec3(0,1,1));
    Light* dirLight = lightEntity.AddComponent(Light{glm::vec3(0.8,0.8,0.8)});
    dirLight->intensity = 1;
    dirLight->type = dirLight->DIRECTIONAL;


}
