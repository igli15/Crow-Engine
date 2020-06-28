//
// Created by Igli milaqi on 24/04/2020.
//

#ifndef CROW_SPAWNSYSTEM_H
#define CROW_SPAWNSYSTEM_H


#include "../../Engine/Feather/System.h"
#include <vector>

class ResourceManager;
class BridgeComponent;
class Player;
class BridgeSelectedEvent;

class SpawnSystem : public System
{
public:
    void OnCreate() override;
    void Init() override;
    void Update(float dt) override;

private:
    void OnBridgeSelected(BridgeSelectedEvent* event);
    BridgeComponent* m_selectedBridge = nullptr;
    Player* m_playerComponent = nullptr;
};


#endif //CROW_SPAWNSYSTEM_H
