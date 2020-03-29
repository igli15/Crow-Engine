//
// Created by Igli milaqi on 25/03/2020.
//

#ifndef CROW_COLLISIONEXITEVENT_H
#define CROW_COLLISIONEXITEVENT_H


#include "../EventQueue/Event.h"
#include "../Feather/EntityHandle.h"

struct CollisionExitEvent : public Event {

public:
    EntityHandle entity1;
    EntityHandle entity2;

    CollisionExitEvent(const EntityHandle &e1, const EntityHandle &e2)
    {
        entity1 = e1;
        entity2 = e2;
    }
};


#endif //CROW_COLLISIONEXITEVENT_H
