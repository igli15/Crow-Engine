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
    ComponentHandle<UnitPathComponent> pathComponentHandle = event->entity.GetComponent<UnitPathComponent>();
    ComponentHandle<SeekComponent> seekComponentHandle = event->entity.GetComponent<SeekComponent>();

    pathComponentHandle.component->currentPathIndex++;
    int pathIndex = pathComponentHandle.component->currentPathIndex ;

    if(pathIndex >= pathComponentHandle.component->pathPoints.size())
    {
        EventQueue::Instance().Publish(new UnitPathCompleteEvent(event->entity.entity));
        world->DestroyEntity(event->entity.entity);
    }
    else
    {
        seekComponentHandle.component->targetPos = pathComponentHandle.component->pathPoints[pathIndex];
    }

    //world->DestroyEntity(event->entity.entity);
}
