//
// Created by Igli milaqi on 27/04/2020.
//

#ifndef CROW_PLAYER_H
#define CROW_PLAYER_H


#include <vector>

class AbstractGroupArchetype;

struct Player
{
    float money = 0.0f;
    AbstractGroupArchetype* selectedUnitArchetype = nullptr;

};


#endif //CROW_PLAYER_H
