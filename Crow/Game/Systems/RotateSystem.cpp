//
// Created by Igli milaqi on 06/03/2020.
//

#include <iostream>
#include <GLFW/glfw3.h>
#include "RotateSystem.h"
#include "../../Engine/Feather/World.h"
#include "../../Engine/Components/Transform.h"
#include "../Components/RotateComponent.h"

void RotateSystem::Init()
{
    System::Init();


    std::cout<<"Initialising System"<<std::endl;
}

void RotateSystem::Update(float dt)
{
    System::Update(0);

    entities = world->EntitiesWith<Transform,RotateComponent>();

    for (auto const& entity : entities)
    {
        Transform& t = world->GetComponent<Transform>(entity);
        RotateComponent& r = world->GetComponent<RotateComponent>(entity);

        t.Rotate(r.rotateSpeed * dt,r.axisOfRotation);
    }

/*
    for (auto const& entity : m_entities)
    {
        Transform& t = world->GetComponent<Transform>(entity);
        RotateComponent& r = world->GetComponent<RotateComponent>(entity);

        t.Rotate(r.rotateSpeed,glm::vec3(0,1,0));
    }
*/
    //This is another way of doing it...

    /*
    ComponentHandle<Transform> t;
    ComponentHandle<RotateComponent> r;

    for (auto const& entity : m_entities)
    {
        world->PopulateHandles(entity,t,r);
        t.component->Rotate(r.component->rotateSpeed,glm::vec3(0,1,1));
    }
     */
}
