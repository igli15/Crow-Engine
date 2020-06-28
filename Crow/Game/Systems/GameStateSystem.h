//
// Created by Igli milaqi on 22/05/2020.
//

#ifndef CROW_GAMESTATESYSTEM_H
#define CROW_GAMESTATESYSTEM_H

#include "../../Engine/Feather/System.h"
#include "../Events/UnitPathCompleteEvent.h"
#include "../Components/Player.h"
#include "../Components/Enemy.h"

//System that manages who is winning.
class GameStateSystem : public System
{
public:
    void OnCreate() override;
    void Init() override;
    void Update(float dt) override;

    void OnUnitPathComplete(UnitPathCompleteEvent* event);

    void CreateYouWinSpriteEntity();
    void CreateYouLoseSpriteEntity();

private:
    Player* m_playerComponent = nullptr;
    Enemy* m_enemyComponent = nullptr;
};


#endif //CROW_GAMESTATESYSTEM_H
