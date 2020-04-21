//
// Created by Igli milaqi on 21/04/2020.
//

#ifndef CROW_STEERINGSYSTEM_H
#define CROW_STEERINGSYSTEM_H


#include "../../Engine/Feather/System.h"

class SteeringSystem : public System
{
    void Init() override;
    void Update(float dt) override;
};


#endif //CROW_STEERINGSYSTEM_H
