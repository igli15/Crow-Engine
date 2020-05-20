//
// Created by Igli milaqi on 27/04/2020.
//

#ifndef CROW_PLAYER_H
#define CROW_PLAYER_H


#include <vector>

class UnitGroupArchetype;

struct Player
{
    float money = 0.0f;
    UnitGroupArchetype* selectedUnitArchetype = nullptr;

};


#endif //CROW_PLAYER_H
