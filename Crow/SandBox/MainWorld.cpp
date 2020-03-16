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

    Shader* shader = Game::Instance()->resourceManager->CreateShader("VertexShader.vs","FragmentShader.fs","unlitShader");
    Model* crysisModel = Game::Instance()->resourceManager->LoadModel((MODEL_PATH + "nanosuit.obj"),"crysis");

    //RegisterSystem<TestSystem>();
    //SetSystemSignature<TestSystem,Transform>();

    RegisterSystem<MeshRendererSystem>();
    SetSystemSignature<MeshRendererSystem,Transform,MeshInfo>();

    ColorMaterial* mat = new ColorMaterial("unlitShader");
    EntityHandle entity  = CreateEntity();

    MeshInfo m;
    m.model = crysisModel;
    m.material = mat;

    entity.AddComponent(Transform{});

    Transform* t = entity.GetComponent<Transform>().component;
    t->Translate(glm::vec3(0,-1.5,-5));
    t->Scale(glm::vec3(0.2f,0.2f,0.2f));
    
    entity.AddComponent(m);

    //ENGINE_LOG("Here");


}
