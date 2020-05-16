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

    //just for testing destruction of entities. TODO remove this in the end
    if(Input::GetKeyDown(GLFW_KEY_BACKSPACE))
    {
        for (int i = 0; i < m_currentSelectedBridge->playerEntitiesOnBridge.size(); ++i)
        {
            world->DestroyEntity(m_currentSelectedBridge->playerEntitiesOnBridge[i]);
        }
        m_currentSelectedBridge->playerEntitiesOnBridge.clear();
    }


}

void BridgeSystem::OnUnitComponentRemoved(ComponentRemovedEvent<UnitComponent> *event)
{
    UnitComponent unitComponent = event->component;

   auto iterator = std::find(unitComponent.bridge->enemyEntitiesOnBridge.begin(),unitComponent.bridge->enemyEntitiesOnBridge.end(),event->entity);

   if(iterator != unitComponent.bridge->enemyEntitiesOnBridge.end())
   {
       unitComponent.bridge->enemyEntitiesOnBridge.erase(iterator);
   }
}

