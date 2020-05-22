//
// Created by Igli milaqi on 16/05/2020.
//

#ifndef CROW_UNITCOMPONENT_H
#define CROW_UNITCOMPONENT_H


#include "BridgeComponent.h"

struct UnitComponent
{
    BridgeComponent* bridge = nullptr;
    float moneyDrop = 0.0f;
    float moneyDropThroughPortal = 0.0f;
    bool isPlayerUnit = true;
};


#endif //CROW_UNITCOMPONENT_H
