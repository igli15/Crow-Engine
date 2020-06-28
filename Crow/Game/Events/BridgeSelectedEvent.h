//
// Created by Igli milaqi on 05/05/2020.
//

#ifndef CROW_BRIDGESELECTEDEVENT_H
#define CROW_BRIDGESELECTEDEVENT_H


#include "../../Engine/EventQueue/Event.h"
#include "../Components/BridgeComponent.h"

class BridgeSelectedEvent : public Event
{
public:
   BridgeComponent* bridge;
   BridgeSelectedEvent(BridgeComponent* pBridge) : bridge(pBridge){};

};


#endif //CROW_BRIDGESELECTEDEVENT_H
