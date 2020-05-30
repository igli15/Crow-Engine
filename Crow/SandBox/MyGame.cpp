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
#include "../Game/Components/BridgeComponent.h"
#include "../Engine/Editor/UnitySceneParser.h"
#include "../Engine/Rendering/Materials/WaterMaterial.h"
#include "../Engine/Rendering/Materials/PortalMaterial.h"
#include "../Engine/Rendering/Materials/UnlitMaterial.h"
#include "../Engine/Rendering/Materials/SpriteMaterial.h"
#include "../Game/Components/CannonComponent.h"
#include "../Game/Components/DamageDealer.h"
#include "../Game/Components/EnemyUnitCollider.h"
#include "../Game/Components/Enemy.h"
#include "../Game/Components/FloatingComponent.h"
#include "../Game/Components/FlockComponent.h"
#include "../Game/Components/HealthComponent.h"
#include "../Game/Components/ProjectileComponent.h"
#include "../Game/Components/RotateComponent.h"
#include "../Game/Components/PlayerUnitCollider.h"
#include "../Game/Components/Player.h"
#include "../Game/Components/SelectedBridgeIndicator.h"
#include "../Game/Components/SeekComponent.h"
#include "../Game/Components/UnitAnimationComponent.h"
#include "../Game/Components/SteeringComponent.h"
#include "../Game/Components/UnitComponent.h"
#include "../Game/Components/UnitPathComponent.h"
#include "../Game/Components/UnitIconComponent.h"
#include "../Game/Components/AutoDestructComponent.h"
#include "../Game/Components/DebugTextComponent.h"
#include "../Engine/Feather/ComponentRegistry.h"

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

void MyGame::AllocateMemory(ComponentRegistry* componentRegistry)
{
    Game::AllocateMemory(componentRegistry);

    componentRegistry->AllocateComponentSet<BridgeComponent>();
    componentRegistry->AllocateComponentSet<CannonComponent>();
    componentRegistry->AllocateComponentSet<DamageDealer>();
    componentRegistry->AllocateComponentSet<Enemy>();
    componentRegistry->AllocateComponentSet<EnemyUnitCollider>();
    componentRegistry->AllocateComponentSet<FloatingComponent>();
    componentRegistry->AllocateComponentSet<FlockComponent>();
    componentRegistry->AllocateComponentSet<HealthComponent>();
    componentRegistry->AllocateComponentSet<Player>();
    componentRegistry->AllocateComponentSet<PlayerUnitCollider>();
    componentRegistry->AllocateComponentSet<ProjectileComponent>();
    componentRegistry->AllocateComponentSet<RotateComponent>();
    componentRegistry->AllocateComponentSet<SeekComponent>();
    componentRegistry->AllocateComponentSet<SelectedBridgeIndicator>();
    componentRegistry->AllocateComponentSet<SteeringComponent>();
    componentRegistry->AllocateComponentSet<UnitAnimationComponent>();
    componentRegistry->AllocateComponentSet<UnitComponent>();
    componentRegistry->AllocateComponentSet<UnitIconComponent>();
    componentRegistry->AllocateComponentSet<UnitPathComponent>();
    componentRegistry->AllocateComponentSet<AutoDestructComponent>();
    componentRegistry->AllocateComponentSet<DebugTextComponent>();

}
