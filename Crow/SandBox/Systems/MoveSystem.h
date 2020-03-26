//
// Created by Igli milaqi on 25/03/2020.
//

#ifndef CROW_MOVESYSTEM_H
#define CROW_MOVESYSTEM_H


#include "../../Engine/Feather/System.h"
#include "../../Engine/Events/CollisionEnterEvent.h"

struct CollisionEvent;


class MoveSystem : public System {

    void Init() override;
    void Update() override;

    void UpdateMaterials(CollisionEnterEvent* collisionEvent);
};


#endif //CROW_MOVESYSTEM_H
