//
// Created by Igli milaqi on 24/04/2020.
//

#include "BridgeSystem.h"
#include "../../Engine/Feather/World.h"
#include "../Components/BridgeComponent.h"
#include "../../Engine/Core/Input.h"
#include "GLFW/glfw3.h"
#include "../Events/BridgeSelectedEvent.h"
#include "../Components/UnitComponent.h"

void BridgeSystem::OnCreate()
{
    System::OnCreate();

    EventQueue::Instance().Subscribe(this, &BridgeSystem::OnUnitComponentRemoved);
}



void BridgeSystem::Init()
{
    System::Init();

    auto bridgeEntities = world->EntitiesWith<BridgeComponent>();

    for (int i = 0; i < bridgeEntities.size(); ++i)
    {
        BridgeComponent* bridgeComponent = &world->GetComponent<BridgeComponent>(bridgeEntities[i]);
        m_bridges.push_back(bridgeComponent);
    }

    m_currentSelectedBridge = m_bridges[0];

    EventQueue::Instance().Publish(new BridgeSelectedEvent(m_bridges[0]));
}

void BridgeSystem::Update(float dt)
{
    System::Update(dt);

    if(Input::GetKeyDown(GLFW_KEY_1))
    {
        m_currentSelectedBridge = m_bridges[0];
        EventQueue::Instance().Publish(new BridgeSelectedEvent(m_bridges[0]));
    }
    else if(Input::GetKeyDown(GLFW_KEY_2))
    {
        m_currentSelectedBridge = m_bridges[1];
        EventQueue::Instance().Publish(new BridgeSelectedEvent(m_bridges[1]));
    }
    else if(Input::GetKeyDown(GLFW_KEY_3))
    {
        m_currentSelectedBridge = m_bridges[2];
        EventQueue::Instance().Publish(new BridgeSelectedEvent(m_bridges[2]));
    }

}

void BridgeSystem::OnUnitComponentRemoved(ComponentRemovedEvent<UnitComponent> *event)
{
    UnitComponent unitComponent = event->component;

   auto enemyUnitIterator = std::find(unitComponent.bridge->enemyEntitiesOnBridge.begin(),unitComponent.bridge->enemyEntitiesOnBridge.end(),event->entity);

   if(enemyUnitIterator != unitComponent.bridge->enemyEntitiesOnBridge.end())
   {
       unitComponent.bridge->enemyEntitiesOnBridge.erase(enemyUnitIterator);
   }

    auto playerUnitIterator = std::find(unitComponent.bridge->playerEntitiesOnBridge.begin(), unitComponent.bridge->playerEntitiesOnBridge.end(), event->entity);

    if(playerUnitIterator != unitComponent.bridge->playerEntitiesOnBridge.end())
    {
        unitComponent.bridge->playerEntitiesOnBridge.erase(playerUnitIterator);
    }
}

