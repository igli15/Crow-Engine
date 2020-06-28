//
// Created by Igli milaqi on 25/03/2020.
//

#ifndef CROW_RIGIDBODYSYSTEM_H
#define CROW_RIGIDBODYSYSTEM_H


#include "../../Engine/Feather/System.h"
#include "../../Engine/Events/CollisionEnterEvent.h"

struct CollisionEvent;


class RigidbodySystem : public System {

    void Init() override;
    void Update(float dt) override;

};


#endif //CROW_RIGIDBODYSYSTEM_H
