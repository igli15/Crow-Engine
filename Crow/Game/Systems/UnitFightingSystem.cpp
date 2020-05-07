//
// Created by Igli milaqi on 01/05/2020.
//

#include "UnitFightingSystem.h"
#include "../Components/DamageDealer.h"
#include "../Components/HealthComponent.h"
#include "../../Engine/Components/Rigidbody.h"

void UnitFightingSystem::Init()
{
    System::Init();

    EventQueue::Instance().Subscribe(this,&UnitFightingSystem::OnUnitCollisionEnter);
    EventQueue::Instance().Subscribe(this,&UnitFightingSystem::OnUnitCollisionStay);
    EventQueue::Instance().Subscribe(this,&UnitFightingSystem::OnUnitCollisionExit);
}

void UnitFightingSystem::Update(float dt)
{
    System::Update(dt);
}

void UnitFightingSystem::OnUnitCollisionStay(UnitCollisionStayEvent *event)
{
    EntityHandle playerUnitEntity = event->playerEntity;
    EntityHandle enemyUnitHandle = event->enemyEntity;

    ComponentHandle<Rigidbody> playerRb =  playerUnitEntity.GetComponent<Rigidbody>();
    ComponentHandle<Rigidbody> enemyRb =  enemyUnitHandle.GetComponent<Rigidbody>();

    playerRb.component->velocity = glm::vec3(0);
    enemyRb.component->velocity = glm::vec3(0);

    playerRb.component->acceleration = glm::vec3(0);
    enemyRb.component->acceleration = glm::vec3(0);

    Fight(playerUnitEntity,enemyUnitHandle);
}

void UnitFightingSystem::OnUnitCollisionEnter(UnitCollisionEnterEvent * event)
{
    //TODO maybe find a better way to resolve fighting collisions. like rn we cant do this here since it might get skipped if there are multiple units so we
    // have to do it oncollisionstay.

    /*
    EntityHandle playerUnitEntity = event->playerEntity;
    EntityHandle enemyUnitHandle = event->enemyEntity;

    ComponentHandle<Rigidbody> playerRb =  playerUnitEntity.GetComponent<Rigidbody>();
    ComponentHandle<Rigidbody> enemyRb =  enemyUnitHandle.GetComponent<Rigidbody>();

    if(playerRb.component->maxSpeed>0) {
        playerRb.component->oldSpeed = playerRb.component->maxSpeed;
    }
    if(enemyRb.component->maxSpeed>0) {
        enemyRb.component->oldSpeed = enemyRb.component->maxSpeed;
    }

    playerRb.component->maxSpeed = 0;
    enemyRb.component->maxSpeed = 0;
     */
}

void UnitFightingSystem::OnUnitCollisionExit(UnitCollisionExitEvent* event)
{
    /*
    EntityHandle playerUnitEntity = event->playerEntity;
    EntityHandle enemyUnitHandle = event->enemyEntity;

    ComponentHandle<Rigidbody> playerRb =  playerUnitEntity.GetComponent<Rigidbody>();
    ComponentHandle<Rigidbody> enemyRb =  enemyUnitHandle.GetComponent<Rigidbody>();

    if(playerRb.component != nullptr)
    {
        playerRb.component->maxSpeed = playerRb.component->oldSpeed;
    }

    if(enemyRb.component != nullptr)
    {
        enemyRb.component->maxSpeed = enemyRb.component->oldSpeed;
    }
     */
}


void UnitFightingSystem::Fight(EntityHandle firstEntity, EntityHandle secondEntity)
{
    ComponentHandle<DamageDealer> firstDamageDealer = firstEntity.GetComponent<DamageDealer>();
    ComponentHandle<DamageDealer> secondDamageDealer = secondEntity.GetComponent<DamageDealer>();

    if(firstDamageDealer.component == nullptr || secondDamageDealer.component == nullptr) return;

    if(firstDamageDealer.component->damageDealerType == DamageDealer::NONE)
    {
        APP_LOG_WARNING("Damage dealer is of none type returning.....");
        return;
    }

    if(secondDamageDealer.component->damageDealerType == DamageDealer::NONE)
    {
        APP_LOG_WARNING("Damage dealer is of none type returning.....");
        return;
    }


    float firstDmg = firstDamageDealer.component->damageRate;
    float secondDmg = secondDamageDealer.component->damageRate;

    if(firstDamageDealer.component->strongAgainst == secondDamageDealer.component->damageDealerType)
    {
        firstDmg *= 2;
    }

    if(secondDamageDealer.component->strongAgainst == firstDamageDealer.component->damageDealerType)
    {
        secondDmg *= 2;
    }

    ComponentHandle<HealthComponent> firstEntityHealth = firstEntity.GetComponent<HealthComponent>();
    ComponentHandle<HealthComponent> secondEntityHealth = secondEntity.GetComponent<HealthComponent>();

    firstEntityHealth.component->currentHealth -= secondDmg;
    secondEntityHealth.component->currentHealth -= firstDmg;

    if(firstEntityHealth.component->currentHealth <= 0)
    {
        world->DestroyEntity(firstEntity.entity);
    }

    if(secondEntityHealth.component->currentHealth <= 0)
    {
        world->DestroyEntity(secondEntity.entity);
    }

}


