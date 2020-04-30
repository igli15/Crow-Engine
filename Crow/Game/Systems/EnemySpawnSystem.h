//
// Created by Igli milaqi on 30/04/2020.
//

#ifndef CROW_ENEMYSPAWNSYSTEM_H
#define CROW_ENEMYSPAWNSYSTEM_H


#include "../../Engine/Feather/System.h"



class EnemySpawnSystem : public System
{
public:
    void Init() override;
    void Update(float dt) override;

private:
    float counter = 0.0f;

};


#endif //CROW_ENEMYSPAWNSYSTEM_H
