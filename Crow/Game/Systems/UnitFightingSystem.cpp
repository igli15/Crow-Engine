//
// Created by Igli milaqi on 01/05/2020.
//

#include "UnitFightingSystem.h"

void UnitFightingSystem::Init()
{
    System::Init();

    EventQueue::Instance().Subscribe(this,&UnitFightingSystem::OnUnitCollisionEnter);
}

void UnitFightingSystem::Update(float dt)
{
    System::Update(dt);
}

void UnitFightingSystem::OnUnitCollisionEnter(UnitCollisionEnterEvent * event)
{
    ENGINE_LOG("here");

    EntityHandle playerUnitEntity = event->playerEntity;
    EntityHandle enemyUnitHandle = event->enemyEntity;

    world->DestroyEntity(playerUnitEntity.entity);
    world->DestroyEntity(enemyUnitHandle.entity);
}
