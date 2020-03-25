//
// Created by Igli milaqi on 25/03/2020.
//

#ifndef CROW_COLLISIONEVENT_H
#define CROW_COLLISIONEVENT_H


#include "../EventQueue/Event.h"
#include "../Feather/EntityHandle.h"

struct CollisionEvent : public Event {

    EntityHandle entity1;
    EntityHandle entity2;

    CollisionEvent(const EntityHandle& e1,const EntityHandle& e2)
    {
        entity1 = e1;
        entity2 = e2;
    }
};


#endif //CROW_COLLISIONEVENT_H
