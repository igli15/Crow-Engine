//
// Created by Igli milaqi on 05/05/2020.
//

#include "SelectedBridgeIndicatorSystem.h"

#include "../Components/BridgeComponent.h"
#include "../Events/BridgeSelectedEvent.h"
#include "../../Engine/EventQueue/EventQueue.h"
#include "../../Engine/Feather/World.h"
#include "../Components/SelectedBridgeIndicator.h"
#include "../../Engine/Components/Transform.h"

void SelectedBridgeIndicatorSystem::OnCreate()
{
    System::OnCreate();

    EventQueue::Instance().Subscribe(this,&SelectedBridgeIndicatorSystem::OnBridgeSelected);
}

void SelectedBridgeIndicatorSystem::Init()
{
    System::Init();

    Entity indicatorEntity = world->EntitiesWith<SelectedBridgeIndicator>()[0];

    selectedBridgeIndicator = world->GetComponentPtr<SelectedBridgeIndicator>(indicatorEntity);
    bridgeIndicatorTransform = world->GetComponentPtr<Transform>(indicatorEntity);
}


void SelectedBridgeIndicatorSystem::OnBridgeSelected(BridgeSelectedEvent *event)
{
    bridgeIndicatorTransform->SetLocalPosition((event->bridge->startPos + event->bridge->endPos)/ 2.0f);
    bridgeIndicatorTransform->Translate(glm::vec3(0,1,0) *selectedBridgeIndicator->verticalOffset);
}
