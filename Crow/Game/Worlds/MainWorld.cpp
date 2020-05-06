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

void MainWorld::Build()
{
    World::Build();

    ResourceManager* resourceManager = Game::Instance()->resourceManager;

    UnitySceneParser::ParseUnityScene("MainLevel.xml",this,&(MainWorld::ParseGameComponents));

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

    EntityHandle playerEntity = CreateEntity();
    Player* playerComponent = playerEntity.AddComponent<Player>(Player{});

    UnitGroupArchetype* ghostArchetype = CreateUnitGroupArchetype<UnitGroupArchetype>("ghosts");
    ghostArchetype->maxSpeed = 0.02f;
    ghostArchetype->unitMaterial = resourceManager->GetMaterial<TranslucentColorMat>("translucentMaterial");
    ghostArchetype->unitModel = resourceManager->GetModel("ghost");
    ghostArchetype->scaleFactor = 0.05;
    ghostArchetype->horizontalDistance = 0.2f;
    ghostArchetype->verticalDistance = 0.2f;
    ghostArchetype->rows = 5;
    ghostArchetype->columns = 5;
    ghostArchetype->unitType = DamageDealer::Sword;
    ghostArchetype->strongAgainstType = DamageDealer::NONE;


    EnemyGroupArchetype* cubeArchetype = CreateUnitGroupArchetype<EnemyGroupArchetype>("cubes");
    cubeArchetype->maxSpeed = 0.02f;
    cubeArchetype->unitMaterial = resourceManager->GetMaterial<TranslucentColorMat>("translucentMaterial");
    cubeArchetype->unitModel = resourceManager->GetModel("golem");
    cubeArchetype->scaleFactor = 0.07f;
    cubeArchetype->horizontalDistance = 0.3f;
    cubeArchetype->verticalDistance = 0.3;
    cubeArchetype->rows = 1;
    cubeArchetype->columns = 1;
    cubeArchetype->unitType = DamageDealer::Pike;
    cubeArchetype->strongAgainstType = DamageDealer::NONE;


    playerComponent->selectedUnitArchetype = ghostArchetype;


    EntityHandle bridgeIndicatorEntity = CreateEntity();
    Transform* transform = bridgeIndicatorEntity.AddComponent(Transform{});
    transform->Rotate(180,glm::vec3(1,0,0));
    transform->Scale(glm::vec3(0.1f,0.2f,0.1f));
    bridgeIndicatorEntity.AddComponent(MeshInfo{resourceManager->GetModel("cone"),resourceManager->GetMaterial<TranslucentColorMat>("defaultMat")});
    bridgeIndicatorEntity.AddComponent(SelectedBridgeIndicator{});


    EntityHandle testProjectileEntity = CreateEntity();
    testProjectileEntity.AddComponent(Transform{});

    Rigidbody rb{};
    rb.maxSpeed = 0.2f;
    testProjectileEntity.AddComponent(rb);

    testProjectileEntity.AddComponent(MeshInfo{resourceManager->GetModel("sphere"),resourceManager->GetMaterial<TranslucentColorMat>("defaultMat")});

    ProjectileComponent projectileComponent{};
    projectileComponent.targetPos = glm::vec3 (6,3,-2);
    testProjectileEntity.AddComponent(projectileComponent);

    EntityHandle targetEntity = CreateEntity();
    Transform* t = targetEntity.AddComponent(Transform{});
    t->Translate(glm::vec3(projectileComponent.targetPos));
    targetEntity.AddComponent(MeshInfo{resourceManager->GetModel("cube"),resourceManager->GetMaterial<TranslucentColorMat>("defaultMat")});

}

void MainWorld::ParseGameComponents(rapidxml::xml_node<> *node, EntityHandle entityHandle)
{
    if(strcmp(node->name(), "BridgeComponent") == 0)
    {
        BridgeComponent *bridgeComponent = entityHandle.AddComponent(BridgeComponent{});

        for (rapidxml::xml_attribute<> *a = node->first_attribute();
             a != nullptr;
             a = a->next_attribute()) {
            std::string attributeName = a->name();
            if (attributeName == "startPos")
            {
                bridgeComponent->startPos =  UnitySceneParser::ScanVector3f(a->value());
            }
            else if(attributeName == "endPos")
            {
                bridgeComponent->endPos =  UnitySceneParser::ScanVector3f(a->value());
            }
        }
    }
}
