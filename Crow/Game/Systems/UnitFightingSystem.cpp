//
// Created by Igli milaqi on 01/05/2020.
//

#include "UnitFightingSystem.h"
#include "../Components/DamageDealer.h"
#include "../Components/HealthComponent.h"
#include "../../Engine/Components/Rigidbody.h"
#include "../../Engine/Events/OnUnitDefeatedEvent.h"

void UnitFightingSystem::Init()
{
    System::Init();
}

void UnitFightingSystem::OnCreate()
{
    System::OnCreate();
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

    Rigidbody& playerRb =  playerUnitEntity.GetComponent<Rigidbody>();
    Rigidbody& enemyRb =  enemyUnitHandle.GetComponent<Rigidbody>();

    playerRb.velocity = glm::vec3(0);
    enemyRb.velocity = glm::vec3(0);

    playerRb.acceleration = glm::vec3(0);
    enemyRb.acceleration = glm::vec3(0);

    Fight(playerUnitEntity,enemyUnitHandle);
}

void UnitFightingSystem::OnUnitCollisionEnter(UnitCollisionEnterEvent * event)
{
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
    DamageDealer* firstDamageDealer = firstEntity.GetComponentPtr<DamageDealer>();
    DamageDealer* secondDamageDealer = secondEntity.GetComponentPtr<DamageDealer>();

    if(firstDamageDealer == nullptr || secondDamageDealer == nullptr) return;

    if(firstDamageDealer->damageDealerType == DamageDealer::NONE)
    {
        APP_LOG_WARNING("Damage dealer is of none type returning.....");
        return;
    }

    if(secondDamageDealer->damageDealerType == DamageDealer::NONE)
    {
        APP_LOG_WARNING("Damage dealer is of none type returning.....");
        return;
    }

    float firstDmg = firstDamageDealer->damageRate;
    float secondDmg = secondDamageDealer->damageRate;

    if(firstDamageDealer->strongAgainst == secondDamageDealer->damageDealerType)
    {
        firstDmg *= 2;
    }

    if(secondDamageDealer->strongAgainst == firstDamageDealer->damageDealerType)
    {
        secondDmg *= 2;
    }

    HealthComponent& firstEntityHealth = firstEntity.GetComponent<HealthComponent>();
    HealthComponent& secondEntityHealth = secondEntity.GetComponent<HealthComponent>();

    firstEntityHealth.currentHealth -= secondDmg;
    secondEntityHealth.currentHealth -= firstDmg;

    if(firstDamageDealer->damageDealerType == DamageDealer::Jumping)
    {
        firstEntityHealth.currentHealth = 0;
    }

    if(secondDamageDealer->damageDealerType == DamageDealer::Jumping)
    {
        secondEntityHealth.currentHealth = 0;
    }


    if(firstEntityHealth.currentHealth <= 0)
    {
        EventQueue::Instance().Publish(new OnUnitDefeatedEvent(firstEntity.entity));
        world->DestroyEntity(firstEntity.entity);

    }

    if(secondEntityHealth.currentHealth <= 0)
    {
        EventQueue::Instance().Publish(new OnUnitDefeatedEvent(secondEntity.entity));
        world->DestroyEntity(secondEntity.entity);
    }

}



