//
// Created by Igli milaqi on 24/04/2020.
//

#include "BridgeSystem.h"
#include "../../Engine/Feather/World.h"
#include "../Components/BridgeComponent.h"
#include "../../Engine/Core/Input.h"
#include "GLFW/glfw3.h"

void BridgeSystem::Init()
{
    System::Init();

    auto bridgeEntities = world->EntitiesWith<BridgeComponent>();

    for (int i = 0; i < bridgeEntities.size(); ++i)
    {
        BridgeComponent* bridgeComponent = &world->GetComponent<BridgeComponent>(bridgeEntities[i]);
        m_bridges.push_back(bridgeComponent);
    }

    m_bridges[0]->isSelected = true;
    m_currentSelectedBridge = m_bridges[0];
}

void BridgeSystem::Update(float dt)
{
    System::Update(dt);

    if(Input::GetKeyDown(GLFW_KEY_1))
    {
        m_currentSelectedBridge->isSelected = false;
        m_currentSelectedBridge =  m_bridges[0];
        m_bridges[0]->isSelected = true;
    }
    else if(Input::GetKeyDown(GLFW_KEY_2))
    {
        m_currentSelectedBridge->isSelected = false;
        m_currentSelectedBridge =  m_bridges[1];
        m_bridges[1]->isSelected = true;
    }
    else if(Input::GetKeyDown(GLFW_KEY_3))
    {
        m_currentSelectedBridge->isSelected = false;
        m_currentSelectedBridge =  m_bridges[2];
        m_bridges[2]->isSelected = true;
    }

    //just for testing destruction of entities. TODO remove this in the end
    if(Input::GetKeyDown(GLFW_KEY_BACKSPACE))
    {
        for (int i = 0; i < m_currentSelectedBridge->entitiesOnBridge.size(); ++i)
        {
            world->DestroyEntity(m_currentSelectedBridge->entitiesOnBridge[i]);
        }
        m_currentSelectedBridge->entitiesOnBridge.clear();
    }


}
