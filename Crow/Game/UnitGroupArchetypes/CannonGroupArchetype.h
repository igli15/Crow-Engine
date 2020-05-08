//
// Created by Igli milaqi on 07/05/2020.
//

#ifndef CROW_CANNONGROUPARCHETYPE_H
#define CROW_CANNONGROUPARCHETYPE_H


#include "AbstractGroupArchetype.h"

class CannonGroupArchetype : public AbstractGroupArchetype
{
    virtual EntityHandle Build(World* world,BridgeComponent* bridgeComponent) override;
};


#endif //CROW_CANNONGROUPARCHETYPE_H
