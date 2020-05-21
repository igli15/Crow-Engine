//
// Created by Igli milaqi on 21/05/2020.
//

#ifndef CROW_PLAYERMONEYSYSTEM_H
#define CROW_PLAYERMONEYSYSTEM_H


#include "../../Engine/Feather/System.h"
#include "../Components/EnemyUnitCollider.h"
#include "../../Engine/Events/OnUnitDefeatedEvent.h"

class Player;
class PlayerMoneySystem : public System
{
public:
    void Init() override;
    void Update(float dt) override;

    void OnEnemyDeath(OnUnitDefeatedEvent* event);

private:
    Player* m_playerComponent = nullptr;
};


#endif //CROW_PLAYERMONEYSYSTEM_H
