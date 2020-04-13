//
// Created by Igli milaqi on 17/03/2020.
//

#include "MyGame.h"
#include "Worlds/RotatingGunsWorld.h"
#include "Worlds/TranslucentMaterialTestWorld.h"
#include "Worlds/XmlTestWorld.h"
#include "../Engine/Core/ResourceManager.h"
#include "../Engine/Rendering/Materials/ColorMaterial.h"
#include "Worlds/SpriteRenderingWorld.h"

void MyGame::LoadAssets()
{
    Game::LoadAssets();

    resourceManager->CreateShader("TranslucentVertexShader.vs","TranslucentFragmentShader.fs","translucentShader");
    resourceManager->CreateShader("VertexShader.vs","FragmentShader.fs","litShader");
    resourceManager->CreateShader("SpriteVertexShader.vs","SpriteFragmentShader.fs","spriteShader");

    resourceManager->CreateMaterial<ColorMaterial>("defaultMat");
    //resourceManager->CreateMaterial<ColorMaterial>("cyanMaterial");

    resourceManager->LoadModel((MODEL_PATH + "cube.obj"),"cube");
    resourceManager->LoadModel((MODEL_PATH + "sphere.obj"),"sphere");
    resourceManager->LoadModel((MODEL_PATH + "axis.obj"),"axis");
    resourceManager->LoadModel((MODEL_PATH + "plane.obj"),"plane");
    resourceManager->LoadModel((MODEL_PATH + "lanternCandle.obj"),"lantern");
    resourceManager->LoadModel((MODEL_PATH + "gravestone.obj"),"gravestone");
    resourceManager->LoadModel((MODEL_PATH + "skeleton.obj"),"skeleton");
    resourceManager->LoadModel((MODEL_PATH + "pine.obj"),"pine");
    resourceManager->LoadModel((MODEL_PATH + "ghost1.obj"),"ghost");
    resourceManager->LoadModel((MODEL_PATH + "dragon.obj"),"dragon");

}

void MyGame::Init()
{
    Game::Init();

    //Set the world here!

    //SetWorld(new XmlTestWorld());
    //SetWorld(new PrototypeWorld());
    //SetWorld(new PhysicsTestWorld());
    SetWorld(new TranslucentMaterialTestWorld());
    //SetWorld(new LightingTestWorld());
    //SetWorld(new RotatingGunsWorld());
    //SetWorld(new SpriteRenderingWorld());
}

