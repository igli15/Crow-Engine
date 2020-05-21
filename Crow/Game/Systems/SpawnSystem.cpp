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
        meleeArchetype->Build(world,m_selectedBridge);
    }
    else if(Input::GetKeyDown(GLFW_KEY_W))
    {
        UnitGroupArchetype* tankArchetype = static_cast<MainWorld*>(world)->GetUnitGroupArchetype<UnitGroupArchetype>("playerTank");
        tankArchetype->Build(world,m_selectedBridge);
    }
    else if(Input::GetKeyDown(GLFW_KEY_E))
    {
        UnitGroupArchetype* cannonArchetype = static_cast<MainWorld*>(world)->GetUnitGroupArchetype<UnitGroupArchetype>("playerCannon");
        cannonArchetype->Build(world,m_selectedBridge);
    }
}

void SpawnSystem::Init()
{
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
