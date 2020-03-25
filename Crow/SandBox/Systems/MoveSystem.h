//
// Created by Igli milaqi on 25/03/2020.
//

#ifndef CROW_MOVESYSTEM_H
#define CROW_MOVESYSTEM_H


#include "../../Engine/Feather/System.h"

struct CollisionEvent;


class MoveSystem : public System {

    void Init() override;
    void Update() override;

    void UpdateMaterials(CollisionEvent* collisionEvent);
};


#endif //CROW_MOVESYSTEM_H
