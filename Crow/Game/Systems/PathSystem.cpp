//
// Created by Igli milaqi on 16/05/2020.
//

#include "PathSystem.h"
#include "../../Engine/EventQueue/EventQueue.h"
#include "../../Game/Events/TargetSeekedEvent.h"
#include "../Components/SeekComponent.h"
#include "../Components/UnitPathComponent.h"
#include "../Events/UnitPathCompleteEvent.h"

void PathSystem::Init()
{
    System::Init();
    EventQueue::Instance().Subscribe(this,&PathSystem::OnPathSeeked);
}

void PathSystem::OnPathSeeked(TargetSeekedEvent* event)
{
    UnitPathComponent& pathComponentHandle = event->entity.GetComponent<UnitPathComponent>();
    SeekComponent& seekComponentHandle = event->entity.GetComponent<SeekComponent>();

    pathComponentHandle.currentPathIndex++;
    int pathIndex = pathComponentHandle.currentPathIndex ;

    if(pathIndex >= pathComponentHandle.pathPoints.size())
    {
        EventQueue::Instance().Publish(new UnitPathCompleteEvent(event->entity.entity));
        world->DestroyEntity(event->entity.entity);
    }
    else
    {
        seekComponentHandle.targetPos = pathComponentHandle.pathPoints[pathIndex];
    }

    //world->DestroyEntity(event->entity.entity);
}
