//
// Created by Igli milaqi on 22/05/2020.
//

#include "GameUISystem.h"
#include "../../Engine/Feather/World.h"
#include "../Components/UnitIconComponent.h"
#include "../../Engine/Components/SpriteInfo.h"
#include "../Components/Player.h"

void GameUISystem::Init()
{
    System::Init();

    m_playerComponent = world->GetComponentPtr<Player>(world->EntitiesWith<Player>()[0]);
}

void GameUISystem::Update(float dt)
{
    System::Update(dt);

    auto entities = world->EntitiesWith<UnitIconComponent,SpriteInfo>();

    for (int i = 0; i < entities.size(); ++i)
    {
        UnitIconComponent& unitIconComponent = world->GetComponent<UnitIconComponent>(entities[i]);
        SpriteInfo& spriteInfoComponent = world->GetComponent<SpriteInfo>(entities[i]);

        if(m_playerComponent->money >= unitIconComponent.unitPrice)
        {
            spriteInfoComponent.sprite = unitIconComponent.avaiableSprite;
        }
        else
        {
            spriteInfoComponent.sprite = unitIconComponent.unavaibleSprite;
        }
    }
    
}
