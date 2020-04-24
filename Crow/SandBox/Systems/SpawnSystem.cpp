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

void SpawnSystem::Update(float dt)
{
    System::Update(dt);

    ///spawn the units on the bridge and make them go forward till the end
    if(Input::GetKeyDown(GLFW_KEY_SPACE))
    {
        EntityHandle unitEntity = world->CreateEntity();
        unitEntity.AddComponent<Transform>(Transform{});
        unitEntity.AddComponent<SteeringComponent>(SteeringComponent{});
        unitEntity.AddComponent<SeekComponent>(SeekComponent{glm::vec3 (-3,-2,0)});
        unitEntity.AddComponent<Rigidbody>(Rigidbody{});

        unitEntity.AddComponent<MeshInfo>(MeshInfo{m_resourceManager->GetModel("cube"),m_resourceManager->GetMaterial<ColorMaterial>("defaultMat")});

    }

}

void SpawnSystem::Init()
{
    m_resourceManager = Game::Instance()->resourceManager;
}
