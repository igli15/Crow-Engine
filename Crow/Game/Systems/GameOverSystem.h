//
// Created by Igli milaqi on 13/06/2020.
//

#ifndef CROW_GAMEOVERSYSTEM_H
#define CROW_GAMEOVERSYSTEM_H


#include "../../Engine/Feather/System.h"

class GameOverSystem : public System
{
public:
    void OnEnable() override;
    void Update(float dt) override;
    void OnDisable() override;
};


#endif //CROW_GAMEOVERSYSTEM_H
