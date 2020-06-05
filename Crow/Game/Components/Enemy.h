//
// Created by Igli milaqi on 22/05/2020.
//

#ifndef CROW_ENEMY_H
#define CROW_ENEMY_H

class HealthBarMaterial;

struct Enemy
{
    float health = 100.0f;
    float maxHealth = 100.0f;
    HealthBarMaterial* healthMat = nullptr;
};


#endif //CROW_ENEMY_H
