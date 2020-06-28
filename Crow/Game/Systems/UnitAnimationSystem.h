//
// Created by Igli milaqi on 17/05/2020.
//

#ifndef CROW_UNITANIMATIONSYSTEM_H
#define CROW_UNITANIMATIONSYSTEM_H


#include "../../Engine/Feather/System.h"

class UnitAnimationSystem : public System
{
public:
    void Init() override;
    void Update(float dt) override;
};


#endif //CROW_UNITANIMATIONSYSTEM_H
