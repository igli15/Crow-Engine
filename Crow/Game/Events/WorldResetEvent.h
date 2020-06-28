//
// Created by Igli milaqi on 13/06/2020.
//

#ifndef CROW_WORLDRESETEVENT_H
#define CROW_WORLDRESETEVENT_H


#include "../../Engine/EventQueue/Event.h"

class World;

class WorldResetEvent : public Event
{
public:
    World* world;

    WorldResetEvent(World* pWorld)
    {
        world = pWorld;
    };
};


#endif //CROW_WORLDRESETEVENT_H
