//
// Created by Igli milaqi on 06/05/2020.
//

#include "ProjectileSystem.h"
#include "../../Engine/EventQueue/EventQueue.h"
#include "../../Engine/Components/Rigidbody.h"
#include "../../Engine/Feather/World.h"
#include "../../Engine/Components/Transform.h"

void ProjectileSystem::OnCreate()
{
    System::OnCreate();

    EventQueue::Instance().Subscribe(this,&ProjectileSystem::OnProjectileComponentAdded);
}

void ProjectileSystem::OnProjectileComponentAdded(ComponentAddedEvent<ProjectileComponent> *event)
{
    Entity entity = event->entity;

    Rigidbody* rb = world->GetComponentPtr<Rigidbody>(entity);
    Transform* transform = world->GetComponentPtr<Transform>(entity);

    if(rb == nullptr || transform == nullptr)
    {
        APP_LOG_WARNING("No Rigidbody/Transform attached to this entity returning....");
        return;
    }

    ProjectileComponent& projectile = world->GetComponent<ProjectileComponent>(entity);

    rb->acceleration = glm::vec3(0,projectile.gravity,0);

    glm::vec3 initialVelocity = glm::vec3(0);

    glm::vec3 initUpVelocity = glm::vec3(0,1,0) * glm::sqrt(- 2 * projectile.gravity * projectile.height);

    float timeUp = glm::sqrt(- 2 * projectile.height / projectile.gravity);

    float displacementY = projectile.targetPos.y - transform->WorldPosition().y;

    float timeDown = glm::sqrt( 2 * (displacementY - projectile.height)/ projectile.gravity);

    float timeHorizontal = timeUp + timeDown;

    glm::vec3 displacementXZ =glm::vec3 (projectile.targetPos.x - transform->WorldPosition().x,0,projectile.targetPos.z - transform->WorldPosition().z);

    glm::vec3 initHorizontalVelocity = displacementXZ / (timeHorizontal);

    initialVelocity = initHorizontalVelocity + initUpVelocity;

    rb->velocity = initialVelocity * -glm::sign(projectile.gravity);

}

