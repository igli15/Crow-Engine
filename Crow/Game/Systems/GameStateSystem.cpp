//
// Created by Igli milaqi on 22/05/2020.
//

#include "GameStateSystem.h"
#include "../Components/UnitComponent.h"
#include "../../Engine/Feather/World.h"
#include "../../Engine/Feather/EntityHandle.h"
#include "../Components/DamageDealer.h"
#include "../../Engine/Rendering/Materials/HealthBarMaterial.h"
#include "GameOverSystem.h"
#include "../../Engine/Components/Transform.h"
#include "../../Engine/Core/ResourceManager.h"
#include "../../Engine/Core/Game.h"
#include "../../Engine/Components/SpriteInfo.h"

void GameStateSystem::Init()
{
    System::Init();

    m_playerComponent = world->GetComponentPtr<Player>(world->EntitiesWith<Player>()[0]);
    m_enemyComponent = world->GetComponentPtr<Enemy>(world->EntitiesWith<Enemy>()[0]);
}

void GameStateSystem::Update(float dt)
{
    System::Update(dt);
}

void GameStateSystem::OnUnitPathComplete(UnitPathCompleteEvent *event)
{
    UnitComponent* unitComponent = world->GetComponentPtr<UnitComponent>(event->entity);
    DamageDealer* damageDealer = world->GetComponentPtr<DamageDealer>(event->entity);

    if(unitComponent == nullptr || damageDealer == nullptr) return;

    if(unitComponent->isPlayerUnit)
    {
        m_enemyComponent->health -= damageDealer->damageThroughPortal;
        m_enemyComponent->healthMat->fillAmount = m_enemyComponent->health/m_enemyComponent->maxHealth;
        m_playerComponent->money += unitComponent->moneyDropThroughPortal;
    }
    else
    {
        m_playerComponent->health -= damageDealer->damageThroughPortal;

        m_playerComponent->healthMat->fillAmount = m_playerComponent->health/m_playerComponent->maxHealth;
    }

    //TODO handle the win and lose condition
    if(m_playerComponent->health <= 0)
    {
        APP_LOG(m_playerComponent->health);

        CreateYouLoseSpriteEntity();
        world->EnableSystem<GameOverSystem>();
    }

    if(m_enemyComponent->health <= 0)
    {
        //APP_LOG("PLAYER WON");
        CreateYouWinSpriteEntity();
        world->EnableSystem<GameOverSystem>();
    }
}

void GameStateSystem::CreateYouWinSpriteEntity()
{
    ResourceManager* resourceManager = Game::Instance()->resourceManager;

    float screenWidth = Game::Instance()->screenData.screenWidth;
    float screenHeight = Game::Instance()->screenData.screenHeight;

    const float spriteWidth = 360.0f;
    const float spriteHeight= 320.0f;

    EntityHandle youWinEntity = world->CreateEntity();
    Transform* youWinTransform = youWinEntity.AddComponent<Transform>(Transform{});
    youWinTransform->SetLocalPosition(glm::vec3(screenWidth/2.0f - spriteWidth/2, screenHeight/2  - spriteHeight/2, 0));
    youWinTransform->Scale(glm::vec3(spriteWidth, spriteHeight, 1));
    youWinEntity.AddComponent(SpriteInfo{resourceManager->GetSprite("youWinSprite"), resourceManager->GetMaterial<SpriteMaterial>("stateSprite")});
}

void GameStateSystem::CreateYouLoseSpriteEntity()
{
    ResourceManager* resourceManager = Game::Instance()->resourceManager;

    float screenWidth = Game::Instance()->screenData.screenWidth;
    float screenHeight = Game::Instance()->screenData.screenHeight;

    const float spriteWidth = 360.0f;
    const float spriteHeight= 320.0f;

    EntityHandle youLoseEntity = world->CreateEntity();
    Transform* youLoseTransform = youLoseEntity.AddComponent<Transform>(Transform{});
    youLoseTransform->SetLocalPosition(glm::vec3(screenWidth / 2.0f - spriteWidth / 2, screenHeight / 2 - spriteHeight / 2, 0));
    youLoseTransform->Scale(glm::vec3(spriteWidth, spriteHeight, 1));
    youLoseEntity.AddComponent(SpriteInfo{resourceManager->GetSprite("youLoseSprite"), resourceManager->GetMaterial<SpriteMaterial>("stateSprite")});
}

void GameStateSystem::OnCreate()
{
    System::OnCreate();
    EventQueue::Instance().Subscribe(this,&GameStateSystem::OnUnitPathComplete);
}
