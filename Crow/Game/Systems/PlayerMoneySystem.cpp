//
// Created by Igli milaqi on 21/05/2020.
//

#include "PlayerMoneySystem.h"


#include "../../Engine/Feather/World.h"
#include "../../Engine/Components/Text.h"
#include "../Components/Player.h"
#include "../Components/UnitComponent.h"

void PlayerMoneySystem::Init()
{
    System::Init();

    Entity playerEntity = world->EntitiesWith<Player>()[0];
    m_playerComponent = world->GetComponentPtr<Player>(playerEntity);

}

void PlayerMoneySystem::Update(float dt)
{
    System::Update(dt);

    m_playerComponent->money += m_playerComponent->moneyOverTime * dt;

    m_playerComponent->textComponent->textString = std::to_string((int)m_playerComponent->money);
}

void PlayerMoneySystem::OnEnemyDeath(OnUnitDefeatedEvent* event)
{
    UnitComponent* unitComponent = world->GetComponentPtr<UnitComponent>(event->entity);

    if(unitComponent != nullptr) {
        m_playerComponent->money += unitComponent->moneyDrop;
        world->RemoveComponent<UnitComponent>(event->entity);
    }
}

void PlayerMoneySystem::OnCreate()
{
    System::OnCreate();
    EventQueue::Instance().Subscribe(this,&PlayerMoneySystem::OnEnemyDeath);
}
