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

    resourceManager->LoadModel((MODEL_PATH + "plane.obj"),"plane");
    resourceManager->LoadModel((MODEL_PATH + "sphere.obj"),"sphere");
    resourceManager->LoadModel((MODEL_PATH + "lanternCandle.obj"),"lantern");
    resourceManager->LoadModel((MODEL_PATH + "gravestone.obj"),"gravestone");
    resourceManager->LoadModel((MODEL_PATH + "skeleton.obj"),"skeleton");
    resourceManager->LoadModel((MODEL_PATH + "pine.obj"),"pine");
    resourceManager->LoadModel((MODEL_PATH + "ghost1.obj"),"ghost");
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

