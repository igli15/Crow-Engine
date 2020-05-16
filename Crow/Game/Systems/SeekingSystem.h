//
// Created by Igli milaqi on 21/04/2020.
//

#ifndef CROW_SEEKINGSYSTEM_H
#define CROW_SEEKINGSYSTEM_H


#include <glm/vec3.hpp>
#include "../../Engine/Feather/System.h"
#include "../../Engine/Components/Transform.h"
#include "../../Engine/Components/Rigidbody.h"

class SeekingSystem : public System
{
    void Init() override;
    void Update(float dt) override;

    glm::vec3 DoSeek(Entity entity,Transform& ownerTransform, Rigidbody& ownerRigidBody , glm::vec3 target, float slowingRadius = 0.0f);

};


#endif //CROW_SEEKINGSYSTEM_H
