//
// Created by Igli milaqi on 16/05/2020.
//

#ifndef CROW_TARGETSEEKEDEVENT_H
#define CROW_TARGETSEEKEDEVENT_H


#include "../../Engine/Feather/EntityHandle.h"

class TargetSeekedEvent : public Event
{
public:
    EntityHandle entity;

    TargetSeekedEvent(EntityHandle pEntityHandle) : entity(pEntityHandle) {};
};


#endif //CROW_TARGETSEEKEDEVENT_H
