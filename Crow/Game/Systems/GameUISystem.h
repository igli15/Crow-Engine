//
// Created by Igli milaqi on 22/05/2020.
//

#ifndef CROW_GAMEUISYSTEM_H
#define CROW_GAMEUISYSTEM_H


#include "../../Engine/Feather/System.h"

class Player;
class GameUISystem : public System
{
public:
    void Init() override;
    void Update(float dt) override;

private:
    Player* m_playerComponent = nullptr;
};


#endif //CROW_GAMEUISYSTEM_H
