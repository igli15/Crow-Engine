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
#include "../Game/Systems/AutoDestructSystem.h"
#include "../Engine/Systems/CollisionDetectionSystem.h"
#include "../Game/Systems/BridgeSystem.h"
#include "../Game/Systems/CannonSystem.h"
#include "../Game/Systems/DebugTextSystem.h"
#include "../Game/Systems/EnemySpawnSystem.h"
#include "../Game/Systems/FloatingSystem.h"
#include "../Game/Systems/FlockSeparationSystem.h"
#include "../Game/Systems/GameStateSystem.h"
#include "../Game/Systems/GameUISystem.h"
#include "../Game/Systems/PathSystem.h"
#include "../Game/Systems/PlayerMoneySystem.h"
#include "../Game/Systems/ProjectileSystem.h"
#include "../Game/Systems/RigidbodySystem.h"
#include "../Game/Systems/RotateSystem.h"
#include "../Game/Systems/SeekingSystem.h"
#include "../Game/Systems/SelectedBridgeIndicatorSystem.h"
#include "../Game/Systems/SpawnSystem.h"
#include "../Game/Systems/SteeringSystem.h"
#include "../Game/Systems/UnitAnimationSystem.h"
#include "../Game/Systems/UnitCollisionSystem.h"
#include "../Game/Systems/UnitFightingSystem.h"
#include "../Game/Systems/MainMenuSystem.h"
#include "../Game/Components/MainMenuComponent.h"
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

    //resourceManager->LoadAudioClip("boop.wav","boop")->Play();

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

void MyGame::AllocateMemory()
{
    Game::AllocateMemory();

    m_componentRegistry->AllocateComponentSet<BridgeComponent>(3);
    m_componentRegistry->AllocateComponentSet<CannonComponent>();
    m_componentRegistry->AllocateComponentSet<DamageDealer>();
    m_componentRegistry->AllocateComponentSet<Enemy>(1);
    m_componentRegistry->AllocateComponentSet<EnemyUnitCollider>();
    m_componentRegistry->AllocateComponentSet<FloatingComponent>();
    m_componentRegistry->AllocateComponentSet<FlockComponent>();
    m_componentRegistry->AllocateComponentSet<HealthComponent>();
    m_componentRegistry->AllocateComponentSet<Player>(1);
    m_componentRegistry->AllocateComponentSet<PlayerUnitCollider>();
    m_componentRegistry->AllocateComponentSet<ProjectileComponent>();
    m_componentRegistry->AllocateComponentSet<RotateComponent>();
    m_componentRegistry->AllocateComponentSet<SeekComponent>();
    m_componentRegistry->AllocateComponentSet<SelectedBridgeIndicator>(1);
    m_componentRegistry->AllocateComponentSet<SteeringComponent>();
    m_componentRegistry->AllocateComponentSet<UnitAnimationComponent>();
    m_componentRegistry->AllocateComponentSet<UnitComponent>();
    m_componentRegistry->AllocateComponentSet<UnitIconComponent>();
    m_componentRegistry->AllocateComponentSet<UnitPathComponent>();
    m_componentRegistry->AllocateComponentSet<AutoDestructComponent>();
    m_componentRegistry->AllocateComponentSet<DebugTextComponent>();
    m_componentRegistry->AllocateComponentSet<MainMenuComponent>(1);

    m_systemRegistry->AllocateSystem<MainMenuSystem>();
    m_systemRegistry->AllocateSystem<AutoDestructSystem>();
    m_systemRegistry->AllocateSystem<BridgeSystem>();
    m_systemRegistry->AllocateSystem<CannonSystem>();
    m_systemRegistry->AllocateSystem<DebugTextSystem>();
    m_systemRegistry->AllocateSystem<EnemySpawnSystem>();
    m_systemRegistry->AllocateSystem<FloatingSystem>();
    m_systemRegistry->AllocateSystem<FlockSeparationSystem>();
    m_systemRegistry->AllocateSystem<GameStateSystem>();
    m_systemRegistry->AllocateSystem<GameUISystem>();
    m_systemRegistry->AllocateSystem<PathSystem>();
    m_systemRegistry->AllocateSystem<PlayerMoneySystem>();
    m_systemRegistry->AllocateSystem<ProjectileSystem>();
    m_systemRegistry->AllocateSystem<RigidbodySystem>();
    m_systemRegistry->AllocateSystem<RotateSystem>();
    m_systemRegistry->AllocateSystem<SeekingSystem>();
    m_systemRegistry->AllocateSystem<SelectedBridgeIndicatorSystem>();
    m_systemRegistry->AllocateSystem<SpawnSystem>();
    m_systemRegistry->AllocateSystem<SteeringSystem>();
    m_systemRegistry->AllocateSystem<UnitAnimationSystem>();
    m_systemRegistry->AllocateSystem<UnitCollisionSystem>();
    m_systemRegistry->AllocateSystem<UnitFightingSystem>();



}
