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
    World* world;
    std::set<Entity> m_entities;

    //Called on system creation. be aware
    virtual void OnCreate()
    {

    }
    virtual void Init()
    {

    }

    virtual void Update()
    {

    }

    virtual void Render()
    {

    }

    virtual void PreRender()
    {

    }

};


#endif //CROW_SYSTEM_H
