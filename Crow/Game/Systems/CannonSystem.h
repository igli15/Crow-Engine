//
// Created by Igli milaqi on 07/05/2020.
//

#ifndef CROW_CANNONSYSTEM_H
#define CROW_CANNONSYSTEM_H


#include <glm/vec3.hpp>
#include "../../Engine/Feather/System.h"

class CannonSystem : public System
{
public:
    void OnCreate() override;
    void Update(float dt) override;

private:
    void SpawnProjectile(const glm::vec3& spawnPos,const glm::vec3& target);
};


#endif //CROW_CANNONSYSTEM_H
