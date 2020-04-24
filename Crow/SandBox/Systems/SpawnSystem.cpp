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

void SpawnSystem::Update(float dt)
{
    System::Update(dt);

    ///spawn the units on the bridge and make them go forward till the end
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

        EntityHandle unitEntity = world->CreateEntity();
        Transform* unitTransform = unitEntity.AddComponent<Transform>(Transform{});

        unitTransform->Translate(activeBridge->startPos);

        ENGINE_LOG(activeBridge->startPos.x);
        ENGINE_LOG(activeBridge->startPos.y);
        ENGINE_LOG(activeBridge->startPos.z);

        unitEntity.AddComponent<SteeringComponent>(SteeringComponent{});
        unitEntity.AddComponent<SeekComponent>(SeekComponent{activeBridge->endPos});
        unitEntity.AddComponent<Rigidbody>(Rigidbody{});

        unitEntity.AddComponent<MeshInfo>(MeshInfo{m_resourceManager->GetModel("cube"),m_resourceManager->GetMaterial<ColorMaterial>("defaultMat")});

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
}
