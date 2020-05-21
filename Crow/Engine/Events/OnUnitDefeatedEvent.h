//
// Created by Igli milaqi on 21/05/2020.
//

#ifndef CROW_ONUNITDEFEATEDEVENT_H
#define CROW_ONUNITDEFEATEDEVENT_H


#include "../EventQueue/Event.h"
#include "../Feather/Types.h"

class OnUnitDefeatedEvent : public Event
{
public:
    Entity entity;

    OnUnitDefeatedEvent(Entity defeatedEntity) : entity(defeatedEntity){};
};


#endif //CROW_ONUNITDEFEATEDEVENT_H
