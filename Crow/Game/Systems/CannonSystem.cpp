//
// Created by Igli milaqi on 07/05/2020.
//

#include "CannonSystem.h"
#include "../../Engine/Feather/World.h"
#include "../../Engine/Feather/EntityHandle.h"
#include "../../Game/Components/CannonComponent.h"
#include "../../Engine/Components/Transform.h"
#include "../../Engine/Components/Rigidbody.h"
#include "../Components/ProjectileComponent.h"
#include "../../Engine/Components/MeshInfo.h"
#include "../../Engine/Rendering/Materials/ColorMaterial.h"
#include "../../Engine/Core/Game.h"
#include "../../Engine/Core/ResourceManager.h"
#include "../../Game/Components/BridgeComponent.h"

void CannonSystem::OnCreate()
{
    System::OnCreate();

}

void CannonSystem::Update(float dt)
{
    System::Update(dt);

    auto cannonEntities = world->EntitiesWith<Transform,CannonComponent>();

    for (int i = 0; i < cannonEntities.size(); ++i)
    {
        CannonComponent &cannonComponent = world->GetComponent<CannonComponent>(cannonEntities[i]);
        Transform& transform = world->GetComponent<Transform>(cannonEntities[i]);
        cannonComponent.reloadCounter += dt;

        if(cannonComponent.reloadCounter >= cannonComponent.reloadTime)
        {
            if(cannonComponent.bridgeComponent->enemyEntitiesOnBridge.empty()) continue;

            Entity closestEnemyEntity = *cannonComponent.bridgeComponent->enemyEntitiesOnBridge.begin();
            Transform& closestTransform = world->GetComponent<Transform>(closestEnemyEntity);
            SpawnProjectile(transform.WorldPosition(),closestTransform.WorldPosition());
            cannonComponent.reloadCounter = 0;
        }
    }
}

void CannonSystem::SpawnProjectile(const glm::vec3& spawnPos,const glm::vec3& target)
{
    ResourceManager* resourceManager = Game::Instance()->resourceManager;
    EntityHandle projectileEntity = world->CreateEntity();
    Transform* transform = projectileEntity.AddComponent(Transform{});
    transform->SetLocalScale(glm::vec3(0.3f));
    transform->SetLocalPosition(spawnPos);

    Rigidbody rb{};
    rb.maxSpeed = 0.2f;
    projectileEntity.AddComponent(rb);

    projectileEntity.AddComponent(MeshInfo{resourceManager->GetModel("sphere"), resourceManager->GetMaterial<ColorMaterial>("defaultMat")});

    ProjectileComponent projectileComponent{};
    projectileComponent.targetPos = glm::vec3 (target);
    projectileEntity.AddComponent(projectileComponent);
}
