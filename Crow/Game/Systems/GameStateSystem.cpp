//
// Created by Igli milaqi on 22/05/2020.
//

#include "GameStateSystem.h"
#include "../Components/UnitComponent.h"
#include "../../Engine/Feather/World.h"
#include "../Components/DamageDealer.h"

void GameStateSystem::Init()
{
    System::Init();

    EventQueue::Instance().Subscribe(this,&GameStateSystem::OnUnitPathComplete);
    m_playerComponent = world->GetComponentPtr<Player>(world->EntitiesWith<Player>()[0]);
    m_enemyComponent = world->GetComponentPtr<Enemy>(world->EntitiesWith<Enemy>()[0]);
}

void GameStateSystem::Update(float dt)
{
    System::Update(dt);
}

void GameStateSystem::OnUnitPathComplete(UnitPathCompleteEvent *event)
{
    UnitComponent& unitComponent = world->GetComponent<UnitComponent>(event->entity);
    DamageDealer& damageDealer = world->GetComponent<DamageDealer>(event->entity);

    if(unitComponent.isPlayerUnit)
    {
        m_enemyComponent->health -= damageDealer.damageThroughPortal;
        m_playerComponent->money += unitComponent.moneyDropThroughPortal;
    }
    else
    {
        m_playerComponent->health -= damageDealer.damageThroughPortal;
    }

    //TODO handle the win and lose condition
    if(m_playerComponent->health <= 0)
    {
        //APP_LOG("ENEMY WON");
    }

    if(m_enemyComponent->health <= 0)
    {
        //APP_LOG("PLAYER WON");
    }
}
