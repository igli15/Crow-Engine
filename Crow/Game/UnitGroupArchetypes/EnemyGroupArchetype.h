//
// Created by Igli milaqi on 30/04/2020.
//

#ifndef CROW_ENEMYGROUPARCHETYPE_H
#define CROW_ENEMYGROUPARCHETYPE_H


#include "AbstractGroupArchetype.h"

class EnemyGroupArchetype : public AbstractGroupArchetype
{
public:
    virtual EntityHandle Build(World* world,BridgeComponent* bridgeComponent) override;
};


#endif //CROW_ENEMYGROUPARCHETYPE_H
