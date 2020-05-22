//
// Created by Igli milaqi on 20/04/2020.
//

#include "MainWorld.h"
#include "../../Engine/Editor/UnitySceneParser.h"
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

void MainWorld::Build()
{
    World::Build();

    ResourceManager* resourceManager = Game::Instance()->resourceManager;

    //UnitySceneParser::ParseUnityScene("MainLevel.xml",this,&(MainWorld::ParseGameComponents));
    UnitySceneParser::ParseUnityScene("MainLevel2.xml",this,&(MainWorld::ParseGameComponents));

    RegisterSystem<RigidbodySystem>();
    RegisterSystem<SteeringSystem>();
    RegisterSystem<SeekingSystem>();
    RegisterSystem<SpawnSystem>();
    RegisterSystem<SelectedBridgeIndicatorSystem>();
    RegisterSystem<BridgeSystem>();
    RegisterSystem<EnemySpawnSystem>();
    RegisterSystem<UnitCollisionSystem>();
    RegisterSystem<UnitFightingSystem>();
    RegisterSystem<ProjectileSystem>();
    RegisterSystem<CannonSystem>();
    RegisterSystem<RotateSystem>();
    RegisterSystem<PathSystem>();
    RegisterSystem<UnitAnimationSystem>();
    RegisterSystem<FloatingSystem>();
    RegisterSystem<FlockSeparationSystem>();
    RegisterSystem<PlayerMoneySystem>();
    RegisterSystem<GameUISystem>();
    RegisterSystem<GameStateSystem>();

    EntityHandle playerEntity = CreateEntity();
    Player* playerComponent = playerEntity.AddComponent<Player>(Player{});
    playerComponent->money = 500;

    EntityHandle enemyEntity = CreateEntity();
    Enemy* enemyComponent = enemyEntity.AddComponent<Enemy>(Enemy{});

    UnitGroupArchetype* playerMeleeArchetype = CreateUnitGroupArchetype<UnitGroupArchetype>("playerMelee");
    playerMeleeArchetype->maxSpeed = 0.7f;
    playerMeleeArchetype->unitMaterial = resourceManager->GetMaterial<TranslucentColorMat>("whiteUnlitMat");
    playerMeleeArchetype->unitModel = resourceManager->GetModel("basicUnit");
    playerMeleeArchetype->scaleFactor = 0.1;
    playerMeleeArchetype->maxHorizontalDistance = 0.2f;
    playerMeleeArchetype->maxVerticalDistance = 0.2f;
    playerMeleeArchetype->rows = 4;
    playerMeleeArchetype->columns = 4;
    playerMeleeArchetype->unitType = DamageDealer::MeleeGroup;
    playerMeleeArchetype->strongAgainstType = DamageDealer::NONE;
    playerMeleeArchetype->unitPrice = 35.0f;
    playerMeleeArchetype->moneyDropThroughPortal = 20.0f;

    UnitGroupArchetype* playerTankArchetype = CreateUnitGroupArchetype<UnitGroupArchetype>("playerTank");
    playerTankArchetype->maxSpeed = 0.7f;
    playerTankArchetype->unitMaterial = resourceManager->GetMaterial<TranslucentColorMat>("whiteUnlitMat");
    playerTankArchetype->unitModel = resourceManager->GetModel("basicUnit");
    playerTankArchetype->scaleFactor = 0.5f;
    playerTankArchetype->maxHorizontalDistance = 0.3f;
    playerTankArchetype->maxVerticalDistance = 0.3;
    playerTankArchetype->rows = 1;
    playerTankArchetype->columns = 1;
    playerTankArchetype->unitType = DamageDealer::Tank;
    playerTankArchetype->strongAgainstType = DamageDealer::NONE;
    playerTankArchetype->unitPrice = 35.0f;
    playerTankArchetype->moneyDropThroughPortal = 20.0f;

    UnitGroupArchetype* playerCanon = CreateUnitGroupArchetype<UnitGroupArchetype>("playerCannon");
    playerCanon->maxSpeed = 0.7f;
    playerCanon->unitMaterial = resourceManager->GetMaterial<TranslucentColorMat>("whiteUnlitMat");
    playerCanon->unitModel = resourceManager->GetModel("basicUnit");
    playerCanon->scaleFactor =0.2f;
    playerCanon->maxHorizontalDistance = 1.5f;
    playerCanon->maxVerticalDistance = 1.5f;
    playerCanon->rows = 1;
    playerCanon->columns = 2;
    playerCanon->unitType = DamageDealer::Jumping;
    playerCanon->strongAgainstType = DamageDealer::NONE;
    playerCanon->damageRate = 50;
    playerCanon->colliderRadius = 1.0f;
    playerCanon->unitPrice = 65.0f;
    playerCanon->moneyDropThroughPortal = 20.0f;

    UnitGroupArchetype* enemyGolemArchetype = CreateUnitGroupArchetype<UnitGroupArchetype>("golem");
    enemyGolemArchetype->maxSpeed = 0.7f;
    enemyGolemArchetype->unitMaterial = resourceManager->GetMaterial<TranslucentColorMat>("blackUnlitMat");
    enemyGolemArchetype->unitModel = resourceManager->GetModel("basicUnit");
    enemyGolemArchetype->scaleFactor = 0.5f;
    enemyGolemArchetype->maxHorizontalDistance = 0.3f;
    enemyGolemArchetype->maxVerticalDistance = 0.3;
    enemyGolemArchetype->rows = 1;
    enemyGolemArchetype->columns = 1;
    enemyGolemArchetype->unitType = DamageDealer::Tank;
    enemyGolemArchetype->strongAgainstType = DamageDealer::NONE;
    enemyGolemArchetype->isPlayerUnit = false;
    enemyGolemArchetype->moneyDrop = 25.0f;
    enemyGolemArchetype->damageThroughPortal = 20.0f;

    playerComponent->selectedUnitArchetype = playerMeleeArchetype;

    EntityHandle bridgeIndicatorEntity = CreateEntity();
    Transform* transform = bridgeIndicatorEntity.AddComponent(Transform{});
    transform->Rotate(180,glm::vec3(1,0,0));
    transform->Scale(glm::vec3(0.1f,0.2f,0.1f));
    bridgeIndicatorEntity.AddComponent(MeshInfo{resourceManager->GetModel("cone"),resourceManager->GetMaterial<TranslucentColorMat>("whiteUnlitMat")});
    bridgeIndicatorEntity.AddComponent(SelectedBridgeIndicator{});

    CreateUIEntities(resourceManager);

    EntityHandle textEntity = CreateEntity();
    Transform* textTransform = textEntity.AddComponent(Transform{});
    textTransform->SetLocalPosition(glm::vec3(0,0,0));
    playerComponent->textComponent = textEntity.AddComponent(Text{"money:",glm::vec3(1),1,Game::Instance()->resourceManager->GetFont("roboto")});
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
        entityHandle.GetComponent<MeshInfo>().component->material = waterMaterial;
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
        entityHandle.GetComponent<MeshInfo>().component->material = portalMaterial;
    }
}

void MainWorld::CreateUIEntities(ResourceManager* resourceManager)
{
    //TODO clean this mess
    Game* game = Game::Instance();

    const int screenWidth = game->screenData.screenWidth;
    const int screenHeight = game->screenData.screenHeight;

    const glm::vec2 borderSize{700,150};
    const int borderBottomPadding = 180;

    const int iconSize = 115;

    const int iconBottomPadding = 150;
    const int iconHorizontalPadding = 200;

    UnitGroupArchetype* meleeArchetype = GetUnitGroupArchetype<UnitGroupArchetype>("playerMelee");
    UnitGroupArchetype* tankArchetype = GetUnitGroupArchetype<UnitGroupArchetype>("playerTank");
    UnitGroupArchetype* cannonArchetype = GetUnitGroupArchetype<UnitGroupArchetype>("playerCannon");

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



}
