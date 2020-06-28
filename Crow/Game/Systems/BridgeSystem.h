//
// Created by Igli milaqi on 24/04/2020.
//

#ifndef CROW_BRIDGESYSTEM_H
#define CROW_BRIDGESYSTEM_H


#include "../../Engine/Feather/System.h"
#include "../../Engine/Events/ComponentRemovedEvent.h"
#include "../Components/PlayerUnitCollider.h"
#include "../Components/EnemyUnitCollider.h"
#include <vector>

class BridgeComponent;
class UnitComponent;

class BridgeSystem : public System
{
public:
    void Init() override;
    void Update(float dt) override;
    void OnCreate() override;

    void OnUnitComponentRemoved(ComponentRemovedEvent<UnitComponent>* event);

private:
    std::vector<BridgeComponent*> m_bridges;
    BridgeComponent* m_currentSelectedBridge = nullptr;
};


#endif //CROW_BRIDGESYSTEM_H
