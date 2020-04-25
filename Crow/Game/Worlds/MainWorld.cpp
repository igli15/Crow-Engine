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

#include "../UnitGroupArchetypes/UnitGroupArchetype.h"

void MainWorld::Build()
{
    World::Build();

    UnitySceneParser::ParseUnityScene("MainLevel.xml",this,&(MainWorld::ParseGameComponents));

    RegisterSystem<RigidbodySystem>();
    RegisterSystem<SteeringSystem>();
    RegisterSystem<SeekingSystem>();
    RegisterSystem<SpawnSystem>();
    RegisterSystem<BridgeSystem>();

    CreateUnitGroupArchetype("ghosts");

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

UnitGroupArchetype *MainWorld::CreateUnitGroupArchetype(const std::string& name)
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

UnitGroupArchetype *MainWorld::GetUnitGroupArchetype(const std::string &name)
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
