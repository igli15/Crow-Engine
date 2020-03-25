//
// Created by Igli milaqi on 25/03/2020.
//

#include "CollisionDetectionSystem.h"
#include "../Components/Transform.h"
#include "../Feather/World.h"
#include "../Components/SphereCollider.h"

void CollisionDetectionSystem::Update()
{
    System::Update();

    auto entities = world->EntitiesWith<SphereCollider,Transform>();

    for (int i = 0; i < entities.size(); i++)
    {
        for (int j = i + 1; j < entities.size(); j++)
        {
            Transform& t1 = world->GetComponent<Transform>(entities[i]);
            Transform& t2 = world->GetComponent<Transform>(entities[j]);

            SphereCollider& s1 = world->GetComponent<SphereCollider>(entities[i]);
            SphereCollider& s2 = world->GetComponent<SphereCollider>(entities[j]);

            glm::vec3 distanceVector = t1.LocalPosition() - t2.LocalPosition();
            float distance = glm::length(distanceVector);

            if(distance<= s1.radius * s2.radius)
            {
                ENGINE_LOG("Boom");
            }
        }
    }
}
