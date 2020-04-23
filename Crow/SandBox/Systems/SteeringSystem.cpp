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
        Transform &transform = world->GetComponent<Transform>(entities[entityIndex]);
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

        LookWhereGoing(rigidBody,transform,0.7f * dt);
    }
}

void SteeringSystem::LookWhereGoing(RigidBody& rigidbody,Transform& transform,float angleStep)
{
    if(rigidbody.velocity != glm::vec3(0))
    {
        //avoids the directional vector to be parallel to the up axis
        glm::vec3 upAxis = glm::normalize(transform.GetWorldTransform()[1]);

        //Target rotation is lookat our velocity
        glm::quat targetRot = glm::quatLookAt(glm::normalize(rigidbody.velocity),upAxis);

        //Smoothly rotate towards the target rotation
        glm::quat smoothedRotation = RotateTowards(transform.getLocalRotation(),targetRot,angleStep);

        transform.SetLocalRotation(smoothedRotation);
    }
}

glm::quat SteeringSystem::RotateTowards(glm::quat q1, glm::quat q2, float maxAngle)
{
    if( maxAngle < 0.001f ){
        // No rotation allowed. Prevent dividing by 0 later.
        return q1;
    }

    float cosTheta = dot(q1, q2);

    // q1 and q2 are already equal.
    // Force q2 just to be sure
    if(cosTheta > 0.9999f){
        return q2;
    }

    // Avoid taking the long path around the sphere
    if (cosTheta < 0){
        q1 = q1*-1.0f;
        cosTheta *= -1.0f;
    }

    float angle = acos(cosTheta);

    // If there is only a 2&deg; difference, and we are allowed 5&deg;,
    // then we arrived.
    if (angle < maxAngle){
        return q2;
    }

    float fT = maxAngle / angle;
    angle = maxAngle;

    glm::quat res = (sin((1.0f - fT) * angle) * q1 + sin(fT * angle) * q2) / sin(angle);
    res = normalize(res);
    return res;

}

/*
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
 */
