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

void SpawnSystem::Update(float dt)
{
    System::Update(dt);

    if(Input::GetKeyDown(GLFW_KEY_SPACE))
    {
        BridgeComponent* activeBridge = nullptr;

        for (int i = 0; i < m_bridges.size(); ++i)
        {
            if(m_bridges[i]->isSelected)
            {
                activeBridge = m_bridges[i];
            }
        }


        EntityHandle unitGroupEntity = m_playerComponent->selectedUnitArchetype->Build(world,activeBridge);
        activeBridge->entitiesOnBridge.push_back(unitGroupEntity.entity);
    }

}

void SpawnSystem::Init()
{
    m_resourceManager = Game::Instance()->resourceManager;
    auto bridgeEntities = world->EntitiesWith<BridgeComponent>();

    for (int i = 0; i < bridgeEntities.size(); ++i)
    {
        BridgeComponent* bridgeComponent = &world->GetComponent<BridgeComponent>(bridgeEntities[i]);
        m_bridges.push_back(bridgeComponent);
    }

    Entity playerEntity = world->EntitiesWith<Player>()[0];
    m_playerComponent = &world->GetComponent<Player>(playerEntity);

}
