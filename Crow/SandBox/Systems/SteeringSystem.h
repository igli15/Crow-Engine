//
// Created by Igli milaqi on 21/04/2020.
//

#ifndef CROW_STEERINGSYSTEM_H
#define CROW_STEERINGSYSTEM_H


#include <glm/ext/quaternion_float.hpp>
#include "../../Engine/Feather/System.h"

class RigidBody;
class Transform;

class SteeringSystem : public System
{
    void Init() override;
    void Update(float dt) override;

    void LookWhereGoing(RigidBody& rigidbody,Transform& transform,float angleStep);
    glm::quat RotateTowards(glm::quat from,glm::quat to,float angleStep);
};


#endif //CROW_STEERINGSYSTEM_H
