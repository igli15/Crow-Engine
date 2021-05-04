//
// Created by Igli milaqi on 17/03/2020.
//

#include "MyGame.h"
#include "Worlds/TranslucentMaterialTestWorld.h"
#include "Worlds/XmlTestWorld.h"
#include "../Engine/Core/ResourceManager.h"
#include "../Engine/Rendering/Materials/ColorMaterial.h"
#include "Worlds/SpriteRenderingWorld.h"
#include "../Engine/Feather/EntityHandle.h"
#include "../Engine/Components/Camera.h"
#include "../Engine/Editor/UnitySceneParser.h"
#include "../Engine/Rendering/Materials/WaterMaterial.h"
#include "../Engine/Rendering/Materials/PortalMaterial.h"
#include "../Engine/Rendering/Materials/UnlitMaterial.h"
#include "../Engine/Rendering/Materials/SpriteMaterial.h"
#include "../Engine/Feather/ComponentRegistry.h"
#include "../Engine/Systems/CollisionDetectionSystem.h"
#include "../Engine/Rendering/Materials/HealthBarMaterial.h"


void MyGame::LoadAssets()
{
    Game::LoadAssets();

    resourceManager->LoadFont("Noteworthy.ttf","gameFont");

    resourceManager->CreateShader("TranslucentVertexShader.vs","TranslucentFragmentShader.fs","translucentShader");
    resourceManager->CreateShader("VertexShader.vs","FragmentShader.fs","litShader");
    resourceManager->CreateShader("SpriteVertexShader.vs","SpriteFragmentShader.fs","spriteShader");
    resourceManager->CreateShader("TextureVertexShader.vs","TextureFragmentShader.fs","textureShader");
    resourceManager->CreateShader("WaterVertexShader.vs","WaterFragmentShader.fs","waterShader");
    resourceManager->CreateShader("PortalVertexShader.vs","PortalFragmentShader.fs","portalShader");
    resourceManager->CreateShader("UnlitVertexShader.vs","UnlitFragmentShader.fs","unlitShader");
    resourceManager->CreateShader("HealthBarVertexShader.vs","HealthBarFragmentShader.fs","healthBarShader");

    resourceManager->CreateMaterial<ColorMaterial>("defaultMat");
    resourceManager->CreateMaterial<WaterMaterial>("waterMaterial");
    resourceManager->CreateMaterial<PortalMaterial>("portalMaterial");


    resourceManager->LoadModel(("cube.obj"),"cube");
    resourceManager->LoadModel(("cone.obj"),"cone");
    resourceManager->LoadModel(("sphere.obj"),"sphere");
    resourceManager->LoadModel(("axis.obj"),"axis");
    resourceManager->LoadModel("plane.obj","plane");

    resourceManager->LoadAssetFromAssetsFile("allAssets.asset");
    resourceManager->LoadAssetFromAssetsFile("UnityAssetFile.asset");

    UnlitMaterial* playerBasicUnitMat = resourceManager->CreateMaterial<UnlitMaterial>("whiteUnlitMat");
    playerBasicUnitMat->diffuseTexture = resourceManager->GetTexture("playerBasicUnitDiffuse");

    UnlitMaterial* enemyBasicUnitMat = resourceManager->CreateMaterial<UnlitMaterial>("blackUnlitMat");
    enemyBasicUnitMat->diffuseTexture = resourceManager->GetTexture("enemyBasicUnitDiffuse");

    resourceManager->CreateSprite("playerUnitGroupUISprite",resourceManager->GetTexture("PlayerUnitGroupUI"));
    resourceManager->CreateMaterial<SpriteMaterial>("playerUnitGroupUIMat");

    resourceManager->CreateSprite("uiBackgroundSprite",resourceManager->GetTexture("uiBackground"));
    resourceManager->CreateMaterial<SpriteMaterial>("uiBackgroundMat");

    resourceManager->CreateSprite("uiBorderQSprite",resourceManager->GetTexture("uiBorderQ"));
    resourceManager->CreateMaterial<SpriteMaterial>("uiBorderQMat");

    resourceManager->CreateSprite("uiBorderWSprite",resourceManager->GetTexture("uiBorderW"));
    resourceManager->CreateMaterial<SpriteMaterial>("uiBorderWMat");

    resourceManager->CreateSprite("uiBorderESprite",resourceManager->GetTexture("uiBorderE"));
    resourceManager->CreateMaterial<SpriteMaterial>("uiBorderEMat");


    resourceManager->CreateSprite("uiBorderQSpriteAvaiable",resourceManager->GetTexture("uiBorderQAvaiable"));
    resourceManager->CreateSprite("uiBorderWSpriteAvaiable",resourceManager->GetTexture("uiBorderWAvaiable"));
    resourceManager->CreateSprite("uiBorderESpriteAvaiable",resourceManager->GetTexture("uiBorderEAvaiable"));


    resourceManager->CreateSprite("moneyIconSprite",resourceManager->GetTexture("moneyIcon"));
    resourceManager->CreateMaterial<SpriteMaterial>("moneyIconMat");


    resourceManager->CreateSprite("titleSprite",resourceManager->GetTexture("title"));
    resourceManager->CreateSprite("playIconSprite",resourceManager->GetTexture("playIcon"));
    resourceManager->CreateSprite("quitIconSprite",resourceManager->GetTexture("quitIcon"));
    resourceManager->CreateSprite("menuSelectionIconSprite",resourceManager->GetTexture("menuSelectionIcon"));

    resourceManager->CreateMaterial<SpriteMaterial>("mainMenuIconMat");

    resourceManager->CreateSprite("healthBarSprite",resourceManager->GetTexture("healthBar"));
    resourceManager->CreateMaterial<HealthBarMaterial>("playerHealthBarMat");
    resourceManager->CreateMaterial<HealthBarMaterial>("enemyHealthBarMat");


    resourceManager->CreateSprite("youWinSprite",resourceManager->GetTexture("youWin"));
    resourceManager->CreateSprite("youLoseSprite",resourceManager->GetTexture("youLose"));
    resourceManager->CreateMaterial<SpriteMaterial>("stateSprite");

    resourceManager->LoadSoundBuffer("portalSFX.wav","portalSFX");
    resourceManager->LoadSoundBuffer("drop.wav","drop");
    resourceManager->LoadSoundBuffer("backgroundMusic.wav","backgroundMusic");
}

void MyGame::Init()
{
    Game::Init();



    //Set the world here!

    //SetWorld(new MovementTestWorld());

    //SetWorld(new XmlTestWorld());
    SetWorld(new TranslucentMaterialTestWorld());
    //SetWorld(new RotatingGunsWorld());
    //SetWorld(new SpriteRenderingWorld());

}

void MyGame::AllocateMemory()
{
    Game::AllocateMemory();

    //m_componentRegistry->AllocateComponentSet<BridgeComponent>(3);


    //m_systemRegistry->AllocateSystem<MainMenuSystem>();

}
