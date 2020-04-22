//
// Created by Igli milaqi on 21/04/2020.
//

#include "SteeringSystem.h"
#include "../../Engine/Feather/World.h"
#include "../../Engine/Components/Transform.h"
#include "../../Engine/Components/RigidBody.h"
#include "../Components/SteeringComponent.h"
#include <cmath>

void SteeringSystem::Init()
{
    System::Init();
}

void SteeringSystem::Update(float dt)
{
    System::Update(0);

    auto entities = world->EntitiesWith<RigidBody,SteeringComponent>();

    for (int entityIndex = 0; entityIndex < entities.size(); ++entityIndex)
    {

        RigidBody &rigidBody = world->GetComponent<RigidBody>(entities[entityIndex]);
        SteeringComponent &steeringComponent = world->GetComponent<SteeringComponent>(entities[entityIndex]);

        //Clamp steering
        if(steeringComponent.maxSteeringForce > 0)
        {

            float steeringLength = glm::length(steeringComponent.steering);
            if(steeringLength > steeringComponent.maxSteeringForce)
            {
                steeringComponent.steering = glm::normalize(steeringComponent.steering) * steeringComponent.maxSteeringForce;
            }

        }

        //add steering to the acceleration
        rigidBody.acceleration += steeringComponent.steering;

        steeringComponent.steering = glm::vec3(0);
    }
}

void SteeringSystem::LookWhereGoing(RigidBody& rigidbody,Transform& transform)
{
    if(rigidbody.velocity != glm::vec3(0))
    {
        float angle = glm::degrees(atan2(rigidbody.velocity.y,rigidbody.velocity.x));
        glm::quat rot = glm::angleAxis(angle,glm::vec3(1,0,0));

        
    }
}

glm::quat SteeringSystem::RotateTowards(glm::quat from, glm::quat to, float angleStep)
{
    float angleBetweenQuaternions = 0;

    float kEpsilon = 0.000001f;
    float dot = glm::dot(from,to);

    if(dot > 1.0f - kEpsilon) angleBetweenQuaternions = 0;
    else
    {
       angleBetweenQuaternions =  glm::degrees(glm::acos(glm::min(glm::abs(dot),1.0f)) * 2);
    }

    if(angleBetweenQuaternions == 0) return to;

    return glm::slerp(from,to,glm::min(1.0f,angleStep/angleBetweenQuaternions));
}
