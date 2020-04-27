//
// Created by Igli milaqi on 26/04/2020.
//

#ifndef CROW_UNITSELECTIONSYSTEM_H
#define CROW_UNITSELECTIONSYSTEM_H


#include "../../Engine/Feather/System.h"
#include "../Components/Player.h"

class UnitSelectionSystem : public System
{
public:
    void Init() override;
    void Update(float dt) override;

private:
    Player* m_player;
};


#endif //CROW_UNITSELECTIONSYSTEM_H
