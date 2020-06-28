//
// Created by Igli milaqi on 24/05/2020.
//

#ifndef CROW_DEBUGTEXTSYSTEM_H
#define CROW_DEBUGTEXTSYSTEM_H


#include "../../Engine/Feather/System.h"
class Game;

class DebugTextSystem : public System
{
public:
    void Init() override;
    void Update(float dt) override;

private:
    Game* m_game;

};


#endif //CROW_DEBUGTEXTSYSTEM_H
