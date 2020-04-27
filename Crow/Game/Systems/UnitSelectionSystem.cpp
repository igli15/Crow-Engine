//
// Created by Igli milaqi on 26/04/2020.
//

#include "UnitSelectionSystem.h"
#include "../../Engine/Feather/World.h"
#include "../../Engine/Core/Input.h"
#include "GLFW/glfw3.h"

void UnitSelectionSystem::Init()
{
    System::Init();

    Entity playerEntity = world->EntitiesWith<Player>()[0];
    m_player = &world->GetComponent<Player>(playerEntity);
}

void UnitSelectionSystem::Update(float dt)
{
    System::Update(dt);

    if(Input::GetKeyDown(GLFW_KEY_Q))
    {
       //TODO set player archetype here based on input
    }
}
