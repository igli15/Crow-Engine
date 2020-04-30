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

void MainWorld::Build()
{
    World::Build();

    ResourceManager* resourceManager = Game::Instance()->resourceManager;

    UnitySceneParser::ParseUnityScene("MainLevel.xml",this,&(MainWorld::ParseGameComponents));

    RegisterSystem<RigidbodySystem>();
    RegisterSystem<SteeringSystem>();
    RegisterSystem<SeekingSystem>();
    RegisterSystem<SpawnSystem>();
    RegisterSystem<BridgeSystem>();
    RegisterSystem<UnitSelectionSystem>();
    RegisterSystem<EnemySpawnSystem>();


    EntityHandle playerEntity = CreateEntity();
    Player* playerComponent = playerEntity.AddComponent<Player>(Player{});

    UnitGroupArchetype* ghostArchetype = static_cast<UnitGroupArchetype*>(CreateUnitGroupArchetype("ghosts"));
    ghostArchetype->maxSpeed = 0.01f;
    ghostArchetype->unitMaterial = resourceManager->GetMaterial<TranslucentColorMat>("translucentMaterial");
    ghostArchetype->unitModel = resourceManager->GetModel("ghost");
    ghostArchetype->scaleFactor = 0.1;
    ghostArchetype->horizontalDistance = 0.2f;
    ghostArchetype->verticalDistance = 0.2f;
    ghostArchetype->rows = 2;
    ghostArchetype->columns = 2;

    UnitGroupArchetype* cubeArchetype = static_cast<UnitGroupArchetype*>(CreateUnitGroupArchetype("cubes"));
    cubeArchetype->maxSpeed = 0.01f;
    cubeArchetype->unitMaterial = resourceManager->GetMaterial<TranslucentColorMat>("translucentMaterial");
    cubeArchetype->unitModel = resourceManager->GetModel("golem");
    cubeArchetype->scaleFactor = 0.07f;
    cubeArchetype->horizontalDistance = 0.3f;
    cubeArchetype->verticalDistance = 0.3;
    cubeArchetype->rows = 1;
    cubeArchetype->columns = 1;


    playerComponent->selectedUnitArchetype = ghostArchetype;


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

AbstractGroupArchetype *MainWorld::CreateUnitGroupArchetype(const std::string& name)
{
    auto iterator = m_unitArchetypeMap.find(name);

    if (iterator != m_unitArchetypeMap.end())
    {
        ENGINE_LOG_ERROR("There is already a model with name: " + name);
        throw;
    }

    UnitGroupArchetype* unitGroupArchetype = new UnitGroupArchetype();
    m_unitArchetypeMap.insert(iterator,std::make_pair(name,unitGroupArchetype));
    return unitGroupArchetype;
}

AbstractGroupArchetype *MainWorld::GetUnitGroupArchetype(const std::string &name)
{
    auto iterator = m_unitArchetypeMap.find(name);

    if (iterator == m_unitArchetypeMap.end())
    {
        return nullptr;
    }
    else
    {
        return iterator->second;
    }

}
