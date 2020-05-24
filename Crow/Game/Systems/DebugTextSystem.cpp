//
// Created by Igli milaqi on 24/05/2020.
//

#include "DebugTextSystem.h"
#include "../../Engine/Core/Game.h"
#include "../../Engine/Feather/World.h"
#include "../Components/DebugTextComponent.h"
#include "../Components/UnitComponent.h"
#include "../../Engine/Components/Text.h"


void DebugTextSystem::Init()
{
    System::Init();

    m_game = Game::Instance();
}

void DebugTextSystem::Update(float dt)
{
    System::Update(dt);

    auto entities = world->EntitiesWith<DebugTextComponent>();
    auto unitEntities = world->EntitiesWith<UnitComponent>();

    for (int i = 0; i < entities.size(); ++i)
    {
        DebugTextComponent& debugTextComponent = world->GetComponent<DebugTextComponent>(entities[i]);
        debugTextComponent.unitCountText->textString =  "UnitCount :" + std::to_string(unitEntities.size());
        debugTextComponent.fpsText->textString =  "FPS :" + std::to_string(m_game->timeData.FPS);
    }
}
