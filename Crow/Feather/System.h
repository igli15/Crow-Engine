//
// Created by Igli milaqi on 16/02/2020.
//

#ifndef CROW_SYSTEM_H
#define CROW_SYSTEM_H

#include <set>
#include "Types.h"


class World;

class System {

public:
    World* feather;
    std::set<Entity> m_entities;

    virtual void Init()
    {

    }

    virtual void Update()
    {

    }

};


#endif //CROW_SYSTEM_H
