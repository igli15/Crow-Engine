//
// Created by Igli milaqi on 22/05/2020.
//

#ifndef CROW_UNITPATHCOMPLETEEVENT_H
#define CROW_UNITPATHCOMPLETEEVENT_H


#include "../../Engine/EventQueue/Event.h"
#include "../../Engine/Feather/Types.h"

class UnitPathCompleteEvent : public Event
{
public:
    Entity entity;
    UnitPathCompleteEvent(Entity unitEntity) : entity(unitEntity){};
};
#endif //CROW_UNITPATHCOMPLETEEVENT_H
