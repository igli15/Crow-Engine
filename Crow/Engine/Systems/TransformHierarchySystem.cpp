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

//TODO: Add ComponentRemovedEvent<Transform>


void TransformHierarchySystem::OnTransformRemoved(OnEntityDestroyedEvent* event)
{
    Transform& t = world->GetComponent<Transform>(event->entity);
    t.DestroyAllChildrenEntities();
}

void TransformHierarchySystem::OnComponentAdded(ComponentAddedEvent<Transform> *event)
{
    event->component->m_contextWorld = world;
    event->component->owner = event->entity;

}


