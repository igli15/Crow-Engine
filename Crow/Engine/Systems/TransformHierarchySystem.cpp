//
// Created by Igli milaqi on 29/03/2020.
//

#include "TransformHierarchySystem.h"
#include "../Feather/World.h"

void TransformHierarchySystem::OnCreate()
{
    System::OnCreate();

    EventQueue::Instance().Subscribe(this,&TransformHierarchySystem::OnComponentAdded);
    EventQueue::Instance().Subscribe(this,&TransformHierarchySystem::OnTransformRemoved);
}

void TransformHierarchySystem::OnTransformRemoved(ComponentRemovedEvent<Transform>* event)
{
    event->component.DestroyAllChildrenEntities();
}

void TransformHierarchySystem::OnComponentAdded(ComponentAddedEvent<Transform> *event)
{
    event->component->m_contextWorld = world;
    event->component->owner = event->entity;

}


