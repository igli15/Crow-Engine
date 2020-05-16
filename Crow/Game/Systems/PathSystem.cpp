//
// Created by Igli milaqi on 16/05/2020.
//

#include "PathSystem.h"
#include "../../Engine/EventQueue/EventQueue.h"
#include "../../Game/Events/TargetSeekedEvent.h"

void PathSystem::Init()
{
    System::Init();
    EventQueue::Instance().Subscribe(this,&PathSystem::OnPathSeeked);
}

void PathSystem::OnPathSeeked(TargetSeekedEvent* event)
{
    world->DestroyEntity(event->entity.entity);
}
