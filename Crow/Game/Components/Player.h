//
// Created by Igli milaqi on 27/04/2020.
//

#ifndef CROW_PLAYER_H
#define CROW_PLAYER_H


#include <vector>

class UnitGroupArchetype;
class Text;

struct Player
{
    float money = 0.0f;
    float moneyOverTime = 2.0f;
    float health = 100.0f;
    Text* textComponent = nullptr;
    UnitGroupArchetype* selectedUnitArchetype = nullptr;

};


#endif //CROW_PLAYER_H
