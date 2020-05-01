//
// Created by Igli milaqi on 01/05/2020.
//

#ifndef CROW_UNITCOLLISIONEVENTS_H
#define CROW_UNITCOLLISIONEVENTS_H

#include "../../Engine/Feather/EntityHandle.h"
#include "../../Engine/EventQueue/Event.h"

class UnitCollisionEnterEvent : public Event {

public:
    EntityHandle playerEntity;
    EntityHandle enemyEntity;

    UnitCollisionEnterEvent(const EntityHandle& pPlayerEntity,const EntityHandle& pEnemyEntity)
    {
        playerEntity = pPlayerEntity;
        enemyEntity = pEnemyEntity;
    }
};

class UnitCollisionExitEvent : public Event {

public:
    EntityHandle playerEntity;
    EntityHandle enemyEntity;

    UnitCollisionExitEvent(const EntityHandle& pPlayerEntity,const EntityHandle& pEnemyEntity)
    {
        playerEntity = pPlayerEntity;
        enemyEntity = pEnemyEntity;
    }
};

class UnitCollisionStayEvent : public Event {

public:
    EntityHandle playerEntity;
    EntityHandle enemyEntity;

    UnitCollisionStayEvent(const EntityHandle& pPlayerEntity,const EntityHandle& pEnemyEntity)
    {
        playerEntity = pPlayerEntity;
        enemyEntity = pEnemyEntity;
    }
};



#endif //CROW_UNITCOLLISIONEVENTS_H
