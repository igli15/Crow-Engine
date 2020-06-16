//
// Created by Igli milaqi on 20/04/2020.
//

#include "MainWorld.h"
#include "../../Engine/Editor/UnitySceneParser.h"
#include "../../Engine/Utils/Random.h"
#include "../../Engine/Components/Light.h"
#include "../Components/BridgeComponent.h"
#include "../Systems/BridgeSystem.h"
#include "../Systems/SpawnSystem.h"
#include "../Systems/SeekingSystem.h"
#include "../Systems/SteeringSystem.h"
#include "../Systems/RigidbodySystem.h"

#include "../UnitGroupArchetypes/UnitGroupArchetype.h"
#include "../Components/Player.h"
#include "../../Engine/Core/Game.h"
#include "../../Engine/Core/ResourceManager.h"
#include "../../Engine/Rendering/Materials/TranslucentColorMat.h"
#include "../Systems/EnemySpawnSystem.h"
#include "../Systems/UnitCollisionSystem.h"
#include "../Systems/UnitFightingSystem.h"
#include "../Components/SelectedBridgeIndicator.h"
#include "../Systems/SelectedBridgeIndicatorSystem.h"
#include "../Components/ProjectileComponent.h"
#include "../Systems/ProjectileSystem.h"
#include "../Systems/CannonSystem.h"
#include "../../Engine/Rendering/Materials/WaterMaterial.h"
#include "../Components/RotateComponent.h"
#include "../Systems/RotateSystem.h"
#include "../../Engine/Rendering/Materials/PortalMaterial.h"
#include "../Systems/PathSystem.h"
#include "../Systems/UnitAnimationSystem.h"
#include "../../Engine/Components/SpriteInfo.h"
#include "../Systems/FlockSeparationSystem.h"
#include "../Systems/FloatingSystem.h"
#include "../Systems/PlayerMoneySystem.h"
#include "../../Engine/Components/Text.h"
#include "../Components/UnitIconComponent.h"
#include "../Systems/GameUISystem.h"
#include "../Components/Enemy.h"
#include "../Systems/GameStateSystem.h"
#include "../Systems/AutoDestructSystem.h"
#include "../Components/UnitAnimationComponent.h"
#include "../Components/DebugTextComponent.h"
#include "../Systems/DebugTextSystem.h"
#include "../../Engine/Systems/SpriteRendererSystem.h"
#include "../../Engine/Systems/MeshRendererSystem.h"
#include "../../Engine/Systems/TextRenderingSystem.h"
#include "../../Engine/Systems/TransformHierarchySystem.h"
#include "../../Engine/Systems/CollisionDetectionSystem.h"
#include "../Systems/MainMenuSystem.h"
#include "../Components/MainMenuComponent.h"
#include "../../Engine/Rendering/Materials/HealthBarMaterial.h"
#include "../../Engine/Components/AudioListener.h"
#include "../../Engine/Components/AudioSource.h"
#include "../../Engine/Systems/AudioSourceSystem.h"
#include "../../Engine/Systems/AudioListenerSystem.h"
#include "../Systems/GameOverSystem.h"

void MainWorld::Build()
{
    World::Build();

    ResourceManager* resourceManager = Game::Instance()->resourceManager;

    //UnitySceneParser::ParseUnityScene("MainLevel.xml",this,&(MainWorld::ParseGameComponents));

    RegisterSystem<MeshRendererSystem>();
    RegisterSystem<CollisionDetectionSystem>();
    RegisterSystem<TransformHierarchySystem>();
    RegisterSystem<TextRenderingSystem>();
    RegisterSystem<SpriteRendererSystem>();
    SetSystemSignature<MeshRendererSystem,Transform,MeshInfo>();

    RegisterSystem<AudioListenerSystem>();
    RegisterSystem<AudioSourceSystem>();


    RegisterSystem<MainMenuSystem>();
    RegisterSystem<RigidbodySystem>();
    RegisterSystem<SteeringSystem>();
    RegisterSystem<SeekingSystem>();
    RegisterSystem<SpawnSystem>()->enabled = false;
    RegisterSystem<SelectedBridgeIndicatorSystem>();
    RegisterSystem<BridgeSystem>();
    RegisterSystem<EnemySpawnSystem>()->enabled = false;
    RegisterSystem<UnitCollisionSystem>();
    RegisterSystem<UnitFightingSystem>();
    RegisterSystem<ProjectileSystem>();
    RegisterSystem<CannonSystem>();
    RegisterSystem<RotateSystem>();
    RegisterSystem<PathSystem>();
    RegisterSystem<UnitAnimationSystem>();
    RegisterSystem<FloatingSystem>();
    RegisterSystem<FlockSeparationSystem>();
    RegisterSystem<PlayerMoneySystem>()->enabled = false;
    RegisterSystem<GameUISystem>();
    RegisterSystem<GameStateSystem>();
    RegisterSystem<AutoDestructSystem>();
    RegisterSystem<DebugTextSystem>();
    RegisterSystem<GameOverSystem>()->enabled = false;

    UnitySceneParser::ParseUnityScene("MainLevel2.xml",this,&(MainWorld::ParseGameComponents));


    EntityHandle playerEntity = CreateEntity();
    Player* playerComponent = playerEntity.AddComponent<Player>(Player{});
    playerComponent->money = 50 ;
    playerComponent->health = 100.0f;

    EntityHandle enemyEntity = CreateEntity();
    Enemy* enemyComponent = enemyEntity.AddComponent<Enemy>(Enemy{});
    enemyComponent->health = 100.0f;


    CreateMeleeArchetypes(4,4,0.2f,0.2f,0.1f,0.7f,100.0f,0.3f,0.25f,2.0f,1.0f,1.0f,20.0f);
    CreateTankArchetypes(1,1,0.0f,0.0f,0.5f,0.6f,250.0f,0.3f,0.6f,20.0f,15.0f,5.0f,35.0f);
    CreateCannonArchetypes(1,2,1.5f,1.5f,0.2f,0.7f,100.0f,100.0f,0.5f,30.0f,20.0f,20.0f,65.0f);

    playerComponent->selectedUnitArchetype = GetUnitGroupArchetype<UnitGroupArchetype>("playerMelee");

    EntityHandle bridgeIndicatorEntity = CreateEntity();
    Transform* transform = bridgeIndicatorEntity.AddComponent(Transform{});
    transform->Rotate(180,glm::vec3(1,0,0));
    transform->Scale(glm::vec3(0.1f,0.2f,0.1f));
    bridgeIndicatorEntity.AddComponent(MeshInfo{resourceManager->GetModel("cone"),resourceManager->GetMaterial<TranslucentColorMat>("whiteUnlitMat")});
    bridgeIndicatorEntity.AddComponent(SelectedBridgeIndicator{});

    CreateMainMenu();
    CreateDebugText();

    const glm::vec2 textPos = {1000,20};
    EntityHandle textEntity = CreateEntity();
    Transform* textTransform = textEntity.AddComponent(Transform{});
    textTransform->SetLocalPosition(glm::vec3(textPos.x,textPos.y,0));

    playerComponent->textComponent = textEntity.AddComponent(Text{"",glm::vec3(1),0.6f,resourceManager->GetFont("gameFont")});

    Game::Instance()->fogData.fogColor = {0.2f,0.0f,0.3f};
    Game::Instance()->fogData.fogDensity = 0.09f;
    Game::Instance()->fogData.fogGradient = 2.5f;

    //auto entities = Find<Player>([](Entity e,Player& p){ return p.maxHealth == 0.0f;});
    //APP_LOG(entities.size());
}

void MainWorld::ParseGameComponents(rapidxml::xml_node<> *node, EntityHandle entityHandle)
{
    if(strcmp(node->name(), "BridgeComponent") == 0)
    {
        BridgeComponent *bridgeComponent = entityHandle.AddComponent(BridgeComponent{});
        int pathCount = 0;
        for (rapidxml::xml_attribute<> *a = node->first_attribute();
             a != nullptr;
             a = a->next_attribute()) {
            std::string attributeName = a->name();
            if(attributeName == "pathCount")
            {
               pathCount = atoi(a->value());
            } else
            {
                 for (int i = 0; i < pathCount; ++i)
                {
                    if (attributeName == "Path" + std::to_string(i))
                    {
                        bridgeComponent->pathPoints.push_back( UnitySceneParser::ScanVector3f(a->value()));
                    }
                }
            }
        }
    }
    else if(strcmp(node->name(), "AnimationComponent") == 0)
    {
        UnitAnimationComponent* animationComponent = entityHandle.AddComponent(UnitAnimationComponent{});

        float minSpeed = 0.0f;
        float maxSpeed = 0.0f;

        for (rapidxml::xml_attribute<> *a = node->first_attribute();
             a != nullptr;
             a = a->next_attribute()) {
            std::string attributeName = a->name();
            if (attributeName == "minSpeed")
            {
                minSpeed =  strtof(a->value(), 0);
            }
            else if(attributeName == "maxSpeed")
            {
                maxSpeed = strtof(a->value(), 0);
            }
            else if(attributeName == "height")
            {
                animationComponent->height = strtof(a->value(), 0);
            }
        }

        animationComponent->maxSpeed = Random::RandomRange(minSpeed,maxSpeed);
    }
    else if(strcmp(node->name(), "RotateComponent") == 0)
    {
        RotateComponent* rotateComponent = entityHandle.AddComponent(RotateComponent{});

        for (rapidxml::xml_attribute<> *a = node->first_attribute();
             a != nullptr;
             a = a->next_attribute()) {
            std::string attributeName = a->name();
            if (attributeName == "axisOfRotation")
            {
                rotateComponent->axisOfRotation =  UnitySceneParser::ScanVector3f(a->value());
            }
            else if(attributeName == "rotationSpeed")
            {
                rotateComponent->rotateSpeed = strtof(a->value(), 0);
            }
        }

    }
    else if(strcmp(node->name(), "WaterMaterial") == 0)
    {
        WaterMaterial* waterMaterial = nullptr;
        for (rapidxml::xml_attribute<> *a = node->first_attribute();
             a != nullptr;
             a = a->next_attribute())
        {
            std::string attributeName = a->name();

            if (attributeName == "materialName")
            {
                std::string value(a->value());
                auto material = Game::Instance()->resourceManager->GetMaterial<WaterMaterial>(value);
                if(material == nullptr)
                {
                    waterMaterial = Game::Instance()->resourceManager->CreateMaterial<WaterMaterial>(value);
                }
                else
                {
                    waterMaterial = material;
                }

            }
            else if(attributeName == "waveNoiseTexName")
            {
                std::string value(a->value());
                waterMaterial->waveNoiseTexture = Game::Instance()->resourceManager->GetTexture(value);
            }
            else if(attributeName == "depthGradientTexName")
            {
                std::string value(a->value());
                waterMaterial->depthGradientTexture = Game::Instance()->resourceManager->GetTexture(value);
            }
            else if(attributeName == "foamGradientTexName")
            {
                std::string value(a->value());
                waterMaterial->foamGradientTexture = Game::Instance()->resourceManager->GetTexture(value);
            }
            else if(attributeName == "causticsTexName")
            {
                std::string value(a->value());
                waterMaterial->causticsTexture = Game::Instance()->resourceManager->GetTexture(value);
            }
            else if(attributeName == "mainColor")
            {
                waterMaterial->mainColor = UnitySceneParser::ScanVector3f(a->value());
            }
            else if(attributeName == "foamColor")
            {
                waterMaterial->foamColor = UnitySceneParser::ScanVector3f(a->value());
            }
            else if(attributeName == "noiseSpeed")
            {
                waterMaterial->noiseSpeed = strtof(a->value(), 0);
            }
            else if(attributeName == "causticSpeed")
            {
                waterMaterial->causticSpeed = strtof(a->value(), 0);
            }
            else if(attributeName == "noiseScale")
            {
                waterMaterial->noiseScale = strtof(a->value(), 0);
            }
            else if(attributeName == "distanceScale")
            {
                waterMaterial->distanceScale = strtof(a->value(), 0);
            }
        }
        entityHandle.GetComponent<MeshInfo>().SetMaterial(waterMaterial);
    }
    else if(strcmp(node->name(), "PortalMaterial") == 0)
    {
        PortalMaterial* portalMaterial = nullptr;
        for (rapidxml::xml_attribute<> *a = node->first_attribute();
             a != nullptr;
             a = a->next_attribute())
        {
            std::string attributeName = a->name();

            if (attributeName == "materialName")
            {
                std::string value(a->value());
                auto material = Game::Instance()->resourceManager->GetMaterial<PortalMaterial>(value);
                if(material == nullptr)
                {
                    portalMaterial = Game::Instance()->resourceManager->CreateMaterial<PortalMaterial>(value);
                }
                else
                {
                    portalMaterial = material;
                }

            }
            else if(attributeName == "noiseTextureName")
            {
                std::string value(a->value());
                portalMaterial->noiseTexture = Game::Instance()->resourceManager->GetTexture(value);
            }
            else if(attributeName == "rotationMaskTextureName")
            {
                std::string value(a->value());
                portalMaterial->rotationMaskTexture = Game::Instance()->resourceManager->GetTexture(value);
            }
            else if(attributeName == "glowMaskTextureName")
            {
                std::string value(a->value());
                portalMaterial->portalGlowMask = Game::Instance()->resourceManager->GetTexture(value);
            }
            else if(attributeName == "mainColor")
            {
                portalMaterial->mainColor = UnitySceneParser::ScanVector3f(a->value());
            }
            else if(attributeName == "secondColor")
            {
                portalMaterial->secondColor = UnitySceneParser::ScanVector3f(a->value());
            }
            else if(attributeName == "swirlAmount")
            {
                portalMaterial->swirlAmount = strtof(a->value(), 0);
            }
            else if(attributeName == "rotationSpeed")
            {
                portalMaterial->rotationSpeed = strtof(a->value(), 0);
            }
            else if(attributeName == "scalingSpeed")
            {
                portalMaterial->scalingSpeed = strtof(a->value(), 0);
            }

        }
        entityHandle.GetComponent<MeshInfo>().SetMaterial(portalMaterial);
    }
}

void MainWorld::CreateUIEntities()
{
    Game* game = Game::Instance();
    ResourceManager* resourceManager = game->resourceManager;

    int screenWidth = 1920;
    int screenHeight = 1080;

    glm::vec2 borderSize{700,150};
    int borderBottomPadding = 210;

    int iconSize = 115;

    int iconBottomPadding = 180;
    int iconHorizontalPadding = 180;


    UnitGroupArchetype* meleeArchetype = GetUnitGroupArchetype<UnitGroupArchetype>("playerMelee");
    UnitGroupArchetype* tankArchetype = GetUnitGroupArchetype<UnitGroupArchetype>("playerTank");
    UnitGroupArchetype* cannonArchetype = GetUnitGroupArchetype<UnitGroupArchetype>("playerCannon");

    EntityHandle playerHealthBar = CreateEntity();
    Transform* playerHealthBarTransform = playerHealthBar.AddComponent<Transform>(Transform{});
    playerHealthBarTransform->SetLocalPosition(glm::vec3(200,screenHeight - 120,0));
    playerHealthBarTransform->Scale(glm::vec3(200,30,1));
    auto playerHealthMat = resourceManager->GetMaterial<HealthBarMaterial>("playerHealthBarMat");
    playerHealthMat->noiseMap = resourceManager->GetTexture("flowNoise");
    playerHealthMat->fillColor = glm::vec3(0.0f,13.0f/255.0f,131.0f/255.0f);
    playerHealthMat->emptyColor = glm::vec3(0.3f);
    playerHealthMat->fillAmount = 1.2f;
    playerHealthBar.AddComponent(SpriteInfo{resourceManager->GetSprite("healthBarSprite"),playerHealthMat});
    GetComponent<Player>(EntitiesWith<Player>()[0]).healthMat = playerHealthMat;

    EntityHandle enemyHealthBar = CreateEntity();
    Transform* enemyHealthBarTransform = enemyHealthBar.AddComponent<Transform>(Transform{});
    enemyHealthBarTransform->SetLocalPosition(glm::vec3(screenWidth - 400,screenHeight - 120,0));
    enemyHealthBarTransform->Scale(glm::vec3(200,30,1));
    auto enemyHealthMat = resourceManager->GetMaterial<HealthBarMaterial>("enemyHealthBarMat");
    enemyHealthMat->noiseMap = resourceManager->GetTexture("flowNoise");
    enemyHealthMat->fillColor = glm::vec3(163.0/255.0f,100.0f/255.0f,38.0f/255.0f);
    enemyHealthMat->emptyColor = glm::vec3(0.3f);
    enemyHealthMat->fillAmount = 1.2f;
    enemyHealthBar.AddComponent(SpriteInfo{resourceManager->GetSprite("healthBarSprite"),enemyHealthMat});
    GetComponent<Enemy>(EntitiesWith<Enemy>()[0]).healthMat = enemyHealthMat;

    EntityHandle borderEEntity = CreateEntity();
    Transform* borderETransform = borderEEntity.AddComponent<Transform>(Transform{});
    borderETransform->SetLocalPosition(glm::vec3(screenWidth/2 - iconSize/2 + iconHorizontalPadding,screenHeight - iconBottomPadding,1));
    borderETransform->Scale(glm::vec3(iconSize,iconSize,1));
    borderEEntity.AddComponent(SpriteInfo{resourceManager->GetSprite("uiBorderESprite"),resourceManager->GetMaterial<SpriteMaterial>("uiBorderEMat")});
    borderEEntity.AddComponent<UnitIconComponent>(UnitIconComponent{cannonArchetype->unitPrice,resourceManager->GetSprite("uiBorderESpriteAvaiable"),resourceManager->GetSprite("uiBorderESprite")});

    EntityHandle uiBackgroundEntity = CreateEntity();
    Transform* uiBackgroundTransform = uiBackgroundEntity.AddComponent<Transform>(Transform{});
    uiBackgroundTransform->SetLocalPosition(glm::vec3(screenWidth/2 - borderSize.x/2 ,screenHeight - borderBottomPadding,0));
    uiBackgroundTransform->Scale(glm::vec3(borderSize.x,borderSize.y,1));
    uiBackgroundEntity.AddComponent(SpriteInfo{resourceManager->GetSprite("uiBackgroundSprite"),resourceManager->GetMaterial<SpriteMaterial>("uiBackgroundMat")});

    EntityHandle borderQEntity = CreateEntity();
    Transform* borderQTransform = borderQEntity.AddComponent<Transform>(Transform{});
    borderQTransform->SetLocalPosition(glm::vec3(screenWidth/2 - iconSize/2 - iconHorizontalPadding,screenHeight - iconBottomPadding,1));
    borderQTransform->Scale(glm::vec3(iconSize,iconSize,1));
    borderQEntity.AddComponent(SpriteInfo{resourceManager->GetSprite("uiBorderQSprite"),resourceManager->GetMaterial<SpriteMaterial>("uiBorderQMat")});
    borderQEntity.AddComponent<UnitIconComponent>(UnitIconComponent{meleeArchetype->unitPrice,resourceManager->GetSprite("uiBorderQSpriteAvaiable"),resourceManager->GetSprite("uiBorderQSprite")});


    EntityHandle borderWEntity = CreateEntity();
    Transform* borderWTransform = borderWEntity.AddComponent<Transform>(Transform{});
    borderWTransform->SetLocalPosition(glm::vec3(screenWidth/2 - iconSize/2,screenHeight - iconBottomPadding,1));
    borderWTransform->Scale(glm::vec3(iconSize,iconSize,1));
    borderWEntity.AddComponent(SpriteInfo{resourceManager->GetSprite("uiBorderWSprite"),resourceManager->GetMaterial<SpriteMaterial>("uiBorderWMat")});
    borderWEntity.AddComponent<UnitIconComponent>(UnitIconComponent{tankArchetype->unitPrice,resourceManager->GetSprite("uiBorderWSpriteAvaiable"),resourceManager->GetSprite("uiBorderWSprite")});


    EntityHandle moneyIconEntity = CreateEntity();
    Transform* moneyIconTransform = moneyIconEntity.AddComponent<Transform>(Transform{});
    moneyIconTransform->SetLocalPosition(glm::vec3(screenWidth/2 - 20,screenHeight - 50,0));
    moneyIconTransform->Scale(glm::vec3(56,38,1));

    moneyIconEntity.AddComponent(SpriteInfo{resourceManager->GetSprite("moneyIconSprite"),resourceManager->GetMaterial<SpriteMaterial>("moneyIconMat")});


}

void MainWorld::CreateDebugText()
{
    Game* game = Game::Instance();
    ResourceManager* resourceManager = game->resourceManager;


    EntityHandle textEntity = CreateEntity();
    Transform* textTransform = textEntity.AddComponent(Transform{});
    textTransform->SetLocalPosition(glm::vec3(game->screenData.screenWidth - 200,game->screenData.screenHeight - 50,0));
    Text* fpsText =  textEntity.AddComponent(Text{"FPS:",glm::vec3(1),0.5f,resourceManager->GetFont("roboto")});

    EntityHandle textEntity2 = CreateEntity();
    Transform* textTransform2 = textEntity2.AddComponent(Transform{});
    textTransform2->SetLocalPosition(glm::vec3(game->screenData.screenWidth - 200,game->screenData.screenHeight - 80,0));
    Text* unitCountText = textEntity2.AddComponent(Text{"Unit Count:",glm::vec3(1),0.5f,resourceManager->GetFont("roboto")});
    textEntity2.AddComponent(DebugTextComponent{fpsText,unitCountText});
}


void MainWorld::CreateMainMenu()
{
    ResourceManager* resourceManager = Game::Instance()->resourceManager;

    int screenWidth = Game::Instance()->screenData.screenWidth;
    int screenHeight = Game::Instance()->screenData.screenHeight;

    glm::vec2 titleSize{709,88};
    glm::vec2 playIconSize{107,48};
    glm::vec2 quitIconSize{94,53};
    glm::vec2 selectionIconSize{58,51};

    int titleBottomPadding = 200;

    EntityHandle titleEntity = CreateEntity();
    Transform* titleTransform = titleEntity.AddComponent<Transform>(Transform{});
    titleTransform->SetLocalPosition(glm::vec3(screenWidth/2 - titleSize.x/2 ,titleBottomPadding,0));
    titleTransform->Scale(glm::vec3(titleSize.x,titleSize.y,1));
    titleEntity.AddComponent(SpriteInfo{resourceManager->GetSprite("titleSprite"),resourceManager->GetMaterial<SpriteMaterial>("mainMenuIconMat")});
    MainMenuComponent* menuComponent = titleEntity.AddComponent(MainMenuComponent{});

    EntityHandle playIconEntity = CreateEntity();
    Transform* playIconTransform = playIconEntity.AddComponent<Transform>(Transform{});
    playIconTransform->SetLocalPosition(glm::vec3(screenWidth/2 - playIconSize.x/2 ,titleBottomPadding + 200,0));
    playIconTransform->Scale(glm::vec3(playIconSize.x,playIconSize.y,1));
    playIconEntity.AddComponent(SpriteInfo{resourceManager->GetSprite("playIconSprite"),resourceManager->GetMaterial<SpriteMaterial>("mainMenuIconMat")});

    EntityHandle menuSelectionEntity = CreateEntity();
    Transform* menuSelectionTransform = menuSelectionEntity.AddComponent<Transform>(Transform{});
    menuSelectionTransform->SetLocalPosition(glm::vec3(screenWidth/2 - selectionIconSize.x/2 - 100,titleBottomPadding + 200,0));
    menuSelectionTransform->Scale(glm::vec3(selectionIconSize.x,selectionIconSize.y,1));
    menuSelectionEntity.AddComponent(SpriteInfo{resourceManager->GetSprite("menuSelectionIconSprite"),resourceManager->GetMaterial<SpriteMaterial>("mainMenuIconMat")});

    EntityHandle quitIconEntity = CreateEntity();
    Transform* quitIconTransform = quitIconEntity.AddComponent<Transform>(Transform{});
    quitIconTransform->SetLocalPosition(glm::vec3(screenWidth/2 - quitIconSize.x/2 ,titleBottomPadding + 400,0));
    quitIconTransform->Scale(glm::vec3(quitIconSize.x,quitIconSize.y,1));
    quitIconEntity.AddComponent(SpriteInfo{resourceManager->GetSprite("quitIconSprite"),resourceManager->GetMaterial<SpriteMaterial>("mainMenuIconMat")});



    menuComponent->playButtonHandle = playIconEntity;
    menuComponent->quitButtonHandle = quitIconEntity;
    menuComponent->selectionIconHandle = menuSelectionEntity;
    menuComponent->playButtonYPos = titleBottomPadding + 200;
    menuComponent->quitButtonYPos = titleBottomPadding + 400;

    menuComponent->systemsToEnable.push_back(m_systemRegistry->GetSystem<SpawnSystem>());
    menuComponent->systemsToEnable.push_back(m_systemRegistry->GetSystem<EnemySpawnSystem>());
    menuComponent->systemsToEnable.push_back(m_systemRegistry->GetSystem<PlayerMoneySystem>());
}

void MainWorld::CreateMeleeArchetypes(unsigned int rows, unsigned int columns, float maxHorizontalDistance,
                                      float maxVerticalDistance, float scaleFactor, float maxSpeed, float maxHealth,
                                      float DamageRate, float colliderRadius, float moneyDrop, float moneyThroughPortal,
                                      float dmgThroughPortal, float unitPrice)
{
    ResourceManager* resourceManager = Game::Instance()->resourceManager;

    UnitGroupArchetype* playerMeleeArchetype = CreateUnitGroupArchetype<UnitGroupArchetype>("playerMelee");
    playerMeleeArchetype->maxSpeed = maxSpeed;
    playerMeleeArchetype->unitMaterial = resourceManager->GetMaterial<TranslucentColorMat>("whiteUnlitMat");
    playerMeleeArchetype->unitModel = resourceManager->GetModel("basicUnit");
    playerMeleeArchetype->scaleFactor = scaleFactor;
    playerMeleeArchetype->maxHorizontalDistance = maxHorizontalDistance;
    playerMeleeArchetype->maxVerticalDistance = maxVerticalDistance;
    playerMeleeArchetype->rows = rows;
    playerMeleeArchetype->columns = columns;
    playerMeleeArchetype->unitType = DamageDealer::MeleeGroup;
    playerMeleeArchetype->strongAgainstType = DamageDealer::NONE;
    playerMeleeArchetype->unitPrice = unitPrice;
    playerMeleeArchetype->moneyDropThroughPortal = moneyThroughPortal;
    playerMeleeArchetype->colliderRadius = colliderRadius;
    playerMeleeArchetype->damageThroughPortal = dmgThroughPortal;
    playerMeleeArchetype->damageRate = DamageRate;

    UnitGroupArchetype* enemyMeleeArchetype = CreateUnitGroupArchetype<UnitGroupArchetype>("enemyMelee");
    enemyMeleeArchetype->maxSpeed = maxSpeed;
    enemyMeleeArchetype->unitMaterial = resourceManager->GetMaterial<TranslucentColorMat>("blackUnlitMat");
    enemyMeleeArchetype->unitModel = resourceManager->GetModel("basicUnit");
    enemyMeleeArchetype->scaleFactor = scaleFactor;
    enemyMeleeArchetype->maxHorizontalDistance =maxHorizontalDistance;
    enemyMeleeArchetype->maxVerticalDistance = maxVerticalDistance;
    enemyMeleeArchetype->rows = rows;
    enemyMeleeArchetype->columns = columns;
    enemyMeleeArchetype->unitType = DamageDealer::MeleeGroup;
    enemyMeleeArchetype->strongAgainstType = DamageDealer::NONE;
    enemyMeleeArchetype->moneyDrop = moneyDrop;
    enemyMeleeArchetype->isPlayerUnit = false;
    enemyMeleeArchetype->damageThroughPortal = dmgThroughPortal;
    enemyMeleeArchetype->colliderRadius = colliderRadius;
    enemyMeleeArchetype->damageRate = DamageRate;
}

void MainWorld::CreateTankArchetypes(unsigned int rows, unsigned int columns, float maxHorizontalDistance,
                                     float maxVerticalDistance, float scaleFactor, float maxSpeed, float maxHealth,
                                     float DamageRate, float colliderRadius, float moneyDrop, float moneyThroughPortal,
                                     float dmgThroughPortal, float unitPrice)
{

    ResourceManager* resourceManager = Game::Instance()->resourceManager;

    UnitGroupArchetype* playerTankArchetype = CreateUnitGroupArchetype<UnitGroupArchetype>("playerTank");
    playerTankArchetype->maxSpeed = maxSpeed;
    playerTankArchetype->unitMaterial = resourceManager->GetMaterial<TranslucentColorMat>("whiteUnlitMat");
    playerTankArchetype->unitModel = resourceManager->GetModel("basicUnit");
    playerTankArchetype->scaleFactor = scaleFactor;
    playerTankArchetype->maxHorizontalDistance = maxHorizontalDistance;
    playerTankArchetype->maxVerticalDistance = maxVerticalDistance;
    playerTankArchetype->rows = rows;
    playerTankArchetype->columns = columns;
    playerTankArchetype->unitType = DamageDealer::Tank;
    playerTankArchetype->strongAgainstType = DamageDealer::NONE;
    playerTankArchetype->unitPrice = unitPrice;
    playerTankArchetype->moneyDropThroughPortal =moneyThroughPortal;
    playerTankArchetype->damageRate = DamageRate;
    playerTankArchetype->maxHealth = maxHealth;
    playerTankArchetype->colliderRadius = colliderRadius;
    playerTankArchetype->damageThroughPortal = dmgThroughPortal;

    UnitGroupArchetype* enemyTankArchetype = CreateUnitGroupArchetype<UnitGroupArchetype>("enemyTank");
    enemyTankArchetype->maxSpeed = maxSpeed;
    enemyTankArchetype->unitMaterial = resourceManager->GetMaterial<TranslucentColorMat>("blackUnlitMat");
    enemyTankArchetype->unitModel = resourceManager->GetModel("basicUnit");
    enemyTankArchetype->scaleFactor = scaleFactor;
    enemyTankArchetype->maxHorizontalDistance = maxHorizontalDistance;
    enemyTankArchetype->maxVerticalDistance = maxVerticalDistance;
    enemyTankArchetype->rows = rows;
    enemyTankArchetype->columns = columns;
    enemyTankArchetype->unitType = DamageDealer::Tank;
    enemyTankArchetype->strongAgainstType = DamageDealer::NONE;
    enemyTankArchetype->isPlayerUnit = false;
    enemyTankArchetype->moneyDrop = moneyDrop;
    enemyTankArchetype->damageThroughPortal = dmgThroughPortal;
    enemyTankArchetype->damageRate = DamageRate;
    enemyTankArchetype->maxHealth = maxHealth;
    enemyTankArchetype->colliderRadius = colliderRadius;

}

void MainWorld::CreateCannonArchetypes(unsigned int rows, unsigned int columns, float maxHorizontalDistance,
                                       float maxVerticalDistance, float scaleFactor, float maxSpeed, float maxHealth,
                                       float DamageRate, float colliderRadius, float moneyDrop,
                                       float moneyThroughPortal, float dmgThroughPortal, float unitPrice)
{

    ResourceManager* resourceManager = Game::Instance()->resourceManager;

    UnitGroupArchetype* playerCanon = CreateUnitGroupArchetype<UnitGroupArchetype>("playerCannon");
    playerCanon->maxSpeed = maxSpeed;
    playerCanon->unitMaterial = resourceManager->GetMaterial<TranslucentColorMat>("whiteUnlitMat");
    playerCanon->unitModel = resourceManager->GetModel("basicUnit");
    playerCanon->scaleFactor = scaleFactor;
    playerCanon->maxHorizontalDistance = maxHorizontalDistance;
    playerCanon->maxVerticalDistance = maxVerticalDistance;
    playerCanon->rows = rows;
    playerCanon->columns = columns;
    playerCanon->unitType = DamageDealer::Jumping;
    playerCanon->strongAgainstType = DamageDealer::NONE;
    playerCanon->damageRate = DamageRate;
    playerCanon->colliderRadius = colliderRadius;
    playerCanon->unitPrice = unitPrice;
    playerCanon->moneyDropThroughPortal = moneyThroughPortal;
    playerCanon->damageThroughPortal = dmgThroughPortal;

    UnitGroupArchetype* enemyCannonArchetype = CreateUnitGroupArchetype<UnitGroupArchetype>("enemyCannon");
    enemyCannonArchetype->maxSpeed = maxSpeed;
    enemyCannonArchetype->unitMaterial = resourceManager->GetMaterial<TranslucentColorMat>("blackUnlitMat");
    enemyCannonArchetype->unitModel = resourceManager->GetModel("basicUnit");
    enemyCannonArchetype->scaleFactor = scaleFactor;
    enemyCannonArchetype->maxHorizontalDistance = maxHorizontalDistance;
    enemyCannonArchetype->maxVerticalDistance = maxVerticalDistance;
    enemyCannonArchetype->colliderRadius = colliderRadius;
    enemyCannonArchetype->rows = rows;
    enemyCannonArchetype->columns = columns;
    enemyCannonArchetype->unitType = DamageDealer::Jumping;
    enemyCannonArchetype->strongAgainstType = DamageDealer::NONE;
    enemyCannonArchetype->moneyDrop = moneyDrop;
    enemyCannonArchetype->isPlayerUnit = false;
    enemyCannonArchetype->damageThroughPortal = dmgThroughPortal;
    enemyCannonArchetype->damageRate = DamageRate;

}
