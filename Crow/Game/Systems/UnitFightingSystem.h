//
// Created by Igli milaqi on 01/05/2020.
//

#ifndef CROW_UNITFIGHTINGSYSTEM_H
#define CROW_UNITFIGHTINGSYSTEM_H


#include "../../Engine/Feather/System.h"
#include "../Events/UnitCollisionEvents.h"

class UnitFightingSystem : public System
{
public:
        void Init() override;
        void Update(float dt) override;

        void OnUnitCollisionEnter(UnitCollisionEnterEvent* event);

};


#endif //CROW_UNITFIGHTINGSYSTEM_H
