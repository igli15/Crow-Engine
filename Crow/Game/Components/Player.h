//
// Created by Igli milaqi on 27/04/2020.
//

#ifndef CROW_PLAYER_H
#define CROW_PLAYER_H


#include <vector>

class UnitGroupArchetype;
class Text;
class HealthBarMaterial;
struct Player
{
    float money = 0.0f;
    float moneyOverTime = 2.0f;
    float health = 100.0f;
    float maxHealth = 100.0f;
    Text* textComponent = nullptr;
    HealthBarMaterial* healthMat = nullptr;
    UnitGroupArchetype* selectedUnitArchetype = nullptr;

};


#endif //CROW_PLAYER_H
