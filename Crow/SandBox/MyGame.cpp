//
// Created by Igli milaqi on 17/03/2020.
//

#include "MyGame.h"
#include "Worlds/RotatingGunsWorld.h"
#include "Worlds/LightingTestWorld.h"
#include "Worlds/TranslucentMaterialTestWorld.h"
#include "Worlds/PhysicsTestWorld.h"
#include "Worlds/PrototypeWorld.h"
#include "../Engine/Core/ResourceManager.h"

void MyGame::LoadAssets()
{
    resourceManager->CreateShader("TranslucentVertexShader.vs","TranslucentFragmentShader.fs","translucentShader");
    resourceManager->CreateShader("VertexShader.vs","FragmentShader.fs","litShader");

    Model* planeModel = resourceManager->LoadModel((MODEL_PATH + "plane.obj"),"plane");
    Model* sphereModel = resourceManager->LoadModel((MODEL_PATH + "sphere.obj"),"sphere");
}

void MyGame::Init()
{
    Game::Init();

    //Set the world here!

    SetWorld(new PrototypeWorld());
    //SetWorld(new PhysicsTestWorld());
    //SetWorld(new TranslucentMaterialTestWorld());
    //SetWorld(new LightingTestWorld());
    //SetWorld(new RotatingGunsWorld());
}

