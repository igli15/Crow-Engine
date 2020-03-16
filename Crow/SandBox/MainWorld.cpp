//
// Created by Igli milaqi on 06/03/2020.
//

#include "MainWorld.h"
#include "../Tests/FeatherTest.h"
#include "Systems/TestSystem.h"

#include "../Engine/Components/Transform.h"
#include "../Engine/Systems/MeshRendererSystem.h"
#include "../Engine/Components/MeshInfo.h"
#include "../Engine/Core/Game.h"
#include "../Engine/Core/ResourceManager.h"
#include "../Engine/Rendering/Materials/ColorMaterial.h"

void MainWorld::Build()
{
    World::Build();

    //Register the shader once
    Game::Instance()->resourceManager->CreateShader("VertexShader.vs","FragmentShader.fs","unlitShader");

    //Load the models
    Model* crysisModel = Game::Instance()->resourceManager->LoadModel((MODEL_PATH + "nanosuit.obj"),"crysis");
    Model* gunModel = Game::Instance()->resourceManager->LoadModel((MODEL_PATH + "pistol.obj"),"gunModel");

    RegisterSystem<MeshRendererSystem>();
    SetSystemSignature<MeshRendererSystem,Transform,MeshInfo>();

    ColorMaterial* mat = new ColorMaterial("unlitShader");
    
    EntityHandle entity  = CreateEntity();
    EntityHandle gunEntity  = CreateEntity();

    MeshInfo m{};
    m.model = crysisModel;
    m.material = mat;

    MeshInfo gunMeshInfo{};
    gunMeshInfo.model = gunModel;
    gunMeshInfo.material = mat;
    
    entity.AddComponent(Transform{});

    Transform* t = entity.GetComponent<Transform>().component;
    t->Translate(glm::vec3(3,-1.5,-5));
    t->Scale(glm::vec3(0.2f,0.2f,0.2f));

    gunEntity.AddComponent(Transform{});
    Transform* t2 = gunEntity.GetComponent<Transform>().component;
    t2->Translate(glm::vec3(-3,0,-5));
    t2->Scale(glm::vec3(0.1f,0.1f,0.1f));
    t2->Rotate(-25,glm::vec3(0,1,0));
    
    entity.AddComponent(m);
    gunEntity.AddComponent(gunMeshInfo);
    //ENGINE_LOG("Here");

}
