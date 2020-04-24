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
#include "../Game/Worlds/MainWorld.h"
#include "Worlds/MovementTestWorld.h"
#include "../Engine/Feather/EntityHandle.h"
#include "../Engine/Components/Camera.h"
#include "Components/BridgeComponent.h"
#include "../Engine/Editor/UnitySceneParser.h"

void MyGame::LoadAssets()
{
    Game::LoadAssets();

    resourceManager->CreateShader("TranslucentVertexShader.vs","TranslucentFragmentShader.fs","translucentShader");
    resourceManager->CreateShader("VertexShader.vs","FragmentShader.fs","litShader");
    resourceManager->CreateShader("SpriteVertexShader.vs","SpriteFragmentShader.fs","spriteShader");
    resourceManager->CreateShader("TextureVertexShader.vs","TextureFragmentShader.fs","textureShader");
    resourceManager->CreateMaterial<ColorMaterial>("defaultMat");
    //resourceManager->CreateMaterial<ColorMaterial>("cyanMaterial");

    resourceManager->LoadModel(("cube.obj"),"cube");
    resourceManager->LoadModel(("sphere.obj"),"sphere");
    resourceManager->LoadModel(("axis.obj"),"axis");
    resourceManager->LoadModel(("plane.obj"),"plane");
    resourceManager->LoadModel(("lanternCandle.obj"),"lantern");
    resourceManager->LoadModel(("gravestone.obj"),"gravestone");
    resourceManager->LoadModel(("skeleton.obj"),"skeleton");
    resourceManager->LoadModel(("pine.obj"),"pine");
    resourceManager->LoadModel(("ghost1.obj"),"ghost");
    resourceManager->LoadModel(("dragon.obj"),"dragon");
    resourceManager->LoadModel(("floatingRock.obj"),"floatingRock");

    resourceManager->LoadTexture("container.png","containerDiffuse");
    resourceManager->LoadTexture("containerSpecular.png","containerSpecular");

    resourceManager->LoadTexture("crowIcon.png","crowTexture");
    resourceManager->LoadTexture("matrix.jpg","matrixTexture");

}

void MyGame::Init()
{

    Game::Init();


    MainWorld* mainWorld = new MainWorld();
    SetWorld(mainWorld);

    //Set the world here!


    //SetWorld(new MovementTestWorld());

    //SetWorld(new XmlTestWorld());
    //SetWorld(new TranslucentMaterialTestWorld());
    //SetWorld(new RotatingGunsWorld());
    //SetWorld(new SpriteRenderingWorld());

}
