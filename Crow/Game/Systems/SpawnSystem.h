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

class SpawnSystem : public System
{
public:
    void Init() override;
    void Update(float dt) override;

private:
    ResourceManager* m_resourceManager;
    std::vector<BridgeComponent*> m_bridges;
    Player* m_playerComponent = nullptr;
};


#endif //CROW_SPAWNSYSTEM_H
