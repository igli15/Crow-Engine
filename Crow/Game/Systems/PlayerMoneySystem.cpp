//
// Created by Igli milaqi on 21/05/2020.
//

#include "PlayerMoneySystem.h"


#include "../../Engine/Feather/World.h"
#include "../../Engine/Components/Text.h"
#include "../Components/Player.h"

void PlayerMoneySystem::Init()
{
    System::Init();

    Entity playerEntity = world->EntitiesWith<Player>()[0];
    m_playerComponent = world->GetComponentPtr<Player>(playerEntity);

    EventQueue::Instance().Subscribe(this,&PlayerMoneySystem::OnEnemyDeath);
}

void PlayerMoneySystem::Update(float dt)
{
    System::Update(dt);

    m_playerComponent->money += m_playerComponent->moneyOverTime * dt;

    m_playerComponent->textComponent->textString = std::to_string((int)m_playerComponent->money);
}

void PlayerMoneySystem::OnEnemyDeath(ComponentRemovedEvent<EnemyUnitCollider>* event)
{
    //TODO here take the money from the enemy unit.
    // maybe make another component which is a money component and whn that is destroyed player gets money.

    //TODO this has a bug when the enemy gets destroyed cuz of the teleporter you gain money. To fix this
    // add a new event on enemy dead which is only when player units kill an enemy unit!
    m_playerComponent->money += 25.0f;
}
