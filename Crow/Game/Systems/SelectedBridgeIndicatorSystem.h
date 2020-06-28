//
// Created by Igli milaqi on 05/05/2020.
//

#ifndef CROW_SELECTEDBRIDGEINDICATORSYSTEM_H
#define CROW_SELECTEDBRIDGEINDICATORSYSTEM_H


#include "../../Engine/Feather/System.h"

class Transform;
class SelectedBridgeIndicator;
class BridgeSelectedEvent;

class SelectedBridgeIndicatorSystem : public System
{

public:
    void OnCreate() override;
    void Init() override;

private:
    void OnBridgeSelected(BridgeSelectedEvent* event);

    Transform* bridgeIndicatorTransform;
    SelectedBridgeIndicator* selectedBridgeIndicator;
};


#endif //CROW_SELECTEDBRIDGEINDICATORSYSTEM_H
