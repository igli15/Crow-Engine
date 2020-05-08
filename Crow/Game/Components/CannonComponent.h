//
// Created by Igli milaqi on 07/05/2020.
//

#ifndef CROW_CANNONCOMPONENT_H
#define CROW_CANNONCOMPONENT_H

class BridgeComponent;

struct CannonComponent
{
    BridgeComponent* bridgeComponent = nullptr;
    float reloadTime = 4.0f;
    float reloadCounter = 0.0f;
};


#endif //CROW_CANNONCOMPONENT_H
