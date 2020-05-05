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
#include "../UnitGroupArchetypes/UnitGroupArchetype.h"
#include "../Events/BridgeSelectedEvent.h"

void SpawnSystem::Update(float dt)
{
    System::Update(dt);

    if(Input::GetKeyDown(GLFW_KEY_SPACE))
    {
        EntityHandle unitGroupEntity = m_playerComponent->selectedUnitArchetype->Build(world,m_selectedBridge);
        m_selectedBridge->entitiesOnBridge.push_back(unitGroupEntity.entity);
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
