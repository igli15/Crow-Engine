//
// Created by Igli milaqi on 25/03/2020.
//

#ifndef CROW_COLLISIONENTEREVENT_H
#define CROW_COLLISIONENTEREVENT_H


#include "../Feather/EntityHandle.h"

class CollisionEnterEvent : public Event {

public:
    EntityHandle entity1;
    EntityHandle entity2;

    CollisionEnterEvent(const EntityHandle& e1,const EntityHandle& e2)
    {
        entity1 = e1;
        entity2 = e2;
    }
};


#endif //CROW_COLLISIONENTEREVENT_H
