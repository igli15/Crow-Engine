//
// Created by Igli milaqi on 21/04/2020.
//

#include "SeekingSystem.h"
#include "../../Engine/Debug/Debug.h"
#include "../../Engine/Feather/World.h"
#include "../Components/SteeringComponent.h"
#include "../Components/SeekComponent.h"
#include "../../Engine/EventQueue/EventQueue.h"
#include "../Events/TargetSeekedEvent.h"

void SeekingSystem::Init()
{
    System::Init();
}

void SeekingSystem::Update(float dt)
{
    System::Update(dt);

    auto entities = world->EntitiesWith<Transform,Rigidbody,SteeringComponent,SeekComponent>();

    for (int i = 0; i < entities.size(); ++i)
    {
        Transform& transform = world->GetComponent<Transform>(entities[i]);
        SteeringComponent& steeringComponent = world->GetComponent<SteeringComponent>(entities[i]);
        SeekComponent& seekComponent = world->GetComponent<SeekComponent>(entities[i]);
        Rigidbody& rigidBody = world->GetComponent<Rigidbody>(entities[i]);

        steeringComponent.steering += DoSeek(entities[i],transform,rigidBody,seekComponent.targetPos,0.5f);
    }
}

glm::vec3 SeekingSystem::DoSeek(Entity entity,Transform& ownerTransform, Rigidbody& ownerRigidBody, glm::vec3 target, float endRadius)
{
    glm::vec3 resultForce = glm::vec3(0);

    glm::vec3 toTarget = target - ownerTransform.WorldPosition();
    glm::vec3 desiredVelocity = glm::normalize(toTarget) * ownerRigidBody.maxSpeed;


    float distance = glm::length(toTarget);

    if(distance < endRadius)
    {
        EventQueue::Instance().Publish(new TargetSeekedEvent(EntityHandle{entity,world}));
    }

    resultForce = desiredVelocity - ownerRigidBody.velocity;

    return resultForce;
}
