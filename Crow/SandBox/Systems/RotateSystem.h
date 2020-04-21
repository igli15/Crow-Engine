//
// Created by Igli milaqi on 06/03/2020.
//

#ifndef CROW_TESTSYSTEM_H
#define CROW_TESTSYSTEM_H


#include "../../Engine/Feather/System.h"
#include <vector>

class RotateSystem : public System {


    std::vector<Entity> entities;
    void Init() override;
    void Update(float dt) override;

};


#endif //CROW_TESTSYSTEM_H
