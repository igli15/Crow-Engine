//
// Created by Igli milaqi on 20/04/2020.
//

#include "MainWorld.h"
#include "../../Engine/Editor/UnitySceneParser.h"
#include "../../Engine/Components/Light.h"
#include "../Components/BridgeComponent.h"
#include "../../Engine/Feather/EntityHandle.h"
#include "../Systems/BridgeSystem.h"
#include "../Systems/SpawnSystem.h"
#include "../Systems/SeekingSystem.h"
#include "../Systems/SteeringSystem.h"
#include "../Systems/RigidbodySystem.h"

#include "../UnitGroupArchetypes/AbstractGroupArchetype.h"
#include "../UnitGroupArchetypes/UnitGroupArchetype.h"
#include "../Components/Player.h"
#include "../../Engine/Core/Game.h"
#include "../../Engine/Core/ResourceManager.h"
#include "../../Engine/Rendering/Materials/TranslucentColorMat.h"
#include "../Systems/UnitSelectionSystem.h"
#include "../Systems/EnemySpawnSystem.h"
#include "../UnitGroupArchetypes/EnemyGroupArchetype.h"
#include "../Systems/UnitCollisionSystem.h"
#include "../Systems/UnitFightingSystem.h"
#include "../Components/SelectedBridgeIndicator.h"
#include "../Systems/SelectedBridgeIndicatorSystem.h"
#include "../Components/ProjectileComponent.h"
#include "../Systems/ProjectileSystem.h"
#include "../Systems/CannonSystem.h"
#include "../UnitGroupArchetypes/CannonGroupArchetype.h"
#include "../../Engine/Rendering/Materials/WaterMaterial.h"
#include "../Components/RotateComponent.h"
#include "../Systems/RotateSystem.h"
#include "../../Engine/Rendering/Materials/PortalMaterial.h"
#include "../Systems/PathSystem.h"

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
    RegisterSystem<UnitSelectionSystem>();
    RegisterSystem<EnemySpawnSystem>();
    RegisterSystem<UnitCollisionSystem>();
    RegisterSystem<UnitFightingSystem>();
    RegisterSystem<ProjectileSystem>();
    RegisterSystem<CannonSystem>();
    RegisterSystem<RotateSystem>();
    RegisterSystem<PathSystem>();

    EntityHandle playerEntity = CreateEntity();
    Player* playerComponent = playerEntity.AddComponent<Player>(Player{});

    UnitGroupArchetype* ghostArchetype = CreateUnitGroupArchetype<UnitGroupArchetype>("ghosts");
    ghostArchetype->maxSpeed = 0.7f;
    ghostArchetype->unitMaterial = resourceManager->GetMaterial<TranslucentColorMat>("whiteUnlitMat");
    ghostArchetype->unitModel = resourceManager->GetModel("basicUnit");
    ghostArchetype->scaleFactor = 0.1;
    ghostArchetype->horizontalDistance = 0.2f;
    ghostArchetype->verticalDistance = 0.2f;
    ghostArchetype->rows = 4;
    ghostArchetype->columns = 4;
    ghostArchetype->unitType = DamageDealer::Sword;
    ghostArchetype->strongAgainstType = DamageDealer::NONE;


    EnemyGroupArchetype* enemyGolemArchetype = CreateUnitGroupArchetype<EnemyGroupArchetype>("golem");
    enemyGolemArchetype->maxSpeed = 0.7f;
    enemyGolemArchetype->unitMaterial = resourceManager->GetMaterial<TranslucentColorMat>("blackUnlitMat");
    enemyGolemArchetype->unitModel = resourceManager->GetModel("basicUnit");
    enemyGolemArchetype->scaleFactor = 0.5f;
    enemyGolemArchetype->horizontalDistance = 0.3f;
    enemyGolemArchetype->verticalDistance = 0.3;
    enemyGolemArchetype->rows = 1;
    enemyGolemArchetype->columns = 1;
    enemyGolemArchetype->unitType = DamageDealer::Pike;
    enemyGolemArchetype->strongAgainstType = DamageDealer::NONE;


    CannonGroupArchetype* playerCanon = CreateUnitGroupArchetype<CannonGroupArchetype>("canon");
    playerCanon->maxSpeed = 0.7f;
    playerCanon->unitMaterial = resourceManager->GetMaterial<TranslucentColorMat>("translucentMaterial");
    playerCanon->unitModel = resourceManager->GetModel("canon");
    playerCanon->scaleFactor =1.0f;
    playerCanon->horizontalDistance = 0.3f;
    playerCanon->verticalDistance = 0.3;
    playerCanon->rows = 1;
    playerCanon->columns = 1;
    playerCanon->unitType = DamageDealer::Arrow;
    playerCanon->strongAgainstType = DamageDealer::NONE;
    playerCanon->damageRate = 0;
    playerCanon->colliderRadius = 1.0f;


    playerComponent->selectedUnitArchetype = ghostArchetype;


    EntityHandle bridgeIndicatorEntity = CreateEntity();
    Transform* transform = bridgeIndicatorEntity.AddComponent(Transform{});
    transform->Rotate(180,glm::vec3(1,0,0));
    transform->Scale(glm::vec3(0.1f,0.2f,0.1f));
    bridgeIndicatorEntity.AddComponent(MeshInfo{resourceManager->GetModel("cone"),resourceManager->GetMaterial<TranslucentColorMat>("whiteUnlitMat")});
    bridgeIndicatorEntity.AddComponent(SelectedBridgeIndicator{});

    /*
    EntityHandle testProjectileEntity = CreateEntity();
    testProjectileEntity.AddComponent(Transform{});

    Rigidbody rb{};
    rb.maxSpeed = 0.2f;
    testProjectileEntity.AddComponent(rb);

    testProjectileEntity.AddComponent(MeshInfo{resourceManager->GetModel("sphere"),resourceManager->GetMaterial<TranslucentColorMat>("defaultMat")});

    ProjectileComponent projectileComponent{};
    projectileComponent.targetPos = glm::vec3 (5,0,-5);
    testProjectileEntity.AddComponent(projectileComponent);

    EntityHandle targetEntity = CreateEntity();
    Transform* t = targetEntity.AddComponent(Transform{});
    t->Translate(glm::vec3(projectileComponent.targetPos));
    targetEntity.AddComponent(MeshInfo{resourceManager->GetModel("cube"),resourceManager->GetMaterial<ColorMaterial>("defaultMat")});
    */
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
            if (attributeName == "startPos")
            {
                //bridgeComponent->startPos =  UnitySceneParser::ScanVector3f(a->value());
            }
            else if(attributeName == "endPos")
            {
                //bridgeComponent->endPos =  UnitySceneParser::ScanVector3f(a->value());
            }
            else if(attributeName == "pathCount")
            {
               pathCount = atoi(a->value());
            } else
            {
                 for (int i = 0; i < pathCount; ++i)
                {
                    if (attributeName == "Path" + std::to_string(i))
                    {
                        ENGINE_LOG(a->value());
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
