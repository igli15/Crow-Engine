//
// Created by Igli milaqi on 24/04/2020.
//

#include "SpawnSystem.h"
#include "../../Engine/Core/Input.h"
#include "../../Engine/Feather/World.h"
#include "../../Engine/Feather/EntityHandle.h"
#include "../../Engine/Components/Transform.h"
#include "../Components/SteeringComponent.h"
#include "../Components/SeekComponent.h"
#include "../../Engine/Components/MeshInfo.h"
#include "../../Engine/Core/Game.h"
#include "../../Engine/Core/ResourceManager.h"
#include "../../Engine/Rendering/Materials/ColorMaterial.h"
#include "GLFW/glfw3.h"
#include "../../Engine/Components/Rigidbody.h"
#include "../Components/BridgeComponent.h"
#include "../Components/Player.h"
#include "../../Engine/Components/SphereCollider.h"
#include "../Events/BridgeSelectedEvent.h"
#include "../UnitGroupArchetypes/UnitGroupArchetype.h"
#include "../Worlds/MainWorld.h"

void SpawnSystem::Update(float dt)
{
    System::Update(dt);

    if(Input::GetKeyDown(GLFW_KEY_Q))
    {
        UnitGroupArchetype* meleeArchetype = static_cast<MainWorld*>(world)->GetUnitGroupArchetype<UnitGroupArchetype>("playerMelee");
        if(m_playerComponent->money >= meleeArchetype->unitPrice)
        {
            meleeArchetype->Build(world, m_selectedBridge);
            m_playerComponent->money -= meleeArchetype->unitPrice;
        }
    }
    else if(Input::GetKeyDown(GLFW_KEY_W))
    {

        UnitGroupArchetype* tankArchetype = static_cast<MainWorld*>(world)->GetUnitGroupArchetype<UnitGroupArchetype>("playerTank");
        if(m_playerComponent->money >= tankArchetype->unitPrice)
        {
            tankArchetype->Build(world, m_selectedBridge);
            m_playerComponent->money -= tankArchetype->unitPrice;
        }
    }
    else if(Input::GetKeyDown(GLFW_KEY_E))
    {

        UnitGroupArchetype* cannonArchetype = static_cast<MainWorld*>(world)->GetUnitGroupArchetype<UnitGroupArchetype>("playerCannon");
        if(m_playerComponent->money >= cannonArchetype->unitPrice)
        {
            cannonArchetype->Build(world, m_selectedBridge);
            m_playerComponent->money -= cannonArchetype->unitPrice;
        }
    }
}

void SpawnSystem::Init()
{
    Entity playerEntity = world->EntitiesWith<Player>()[0];
    m_playerComponent = &world->GetComponent<Player>(playerEntity);
}

void SpawnSystem::OnCreate()
{
    System::OnCreate();
    EventQueue::Instance().Subscribe(this,&SpawnSystem::OnBridgeSelected);
}

void SpawnSystem::OnBridgeSelected(BridgeSelectedEvent *event)
{
    m_selectedBridge = event->bridge;
}
