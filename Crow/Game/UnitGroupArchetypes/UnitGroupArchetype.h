//
// Created by Igli milaqi on 25/04/2020.
//

#ifndef CROW_UNITGROUPARCHETYPE_H
#define CROW_UNITGROUPARCHETYPE_H

#include "../../Engine/Feather/EntityHandle.h"
#include "AbstractGroupArchetype.h"

class Model;
class AbstractMaterial;
class BridgeComponent;

class UnitGroupArchetype : public AbstractGroupArchetype
{
public:

    EntityHandle Build(World* world,BridgeComponent* bridge) override;

};


#endif //CROW_UNITGROUPARCHETYPE_H
