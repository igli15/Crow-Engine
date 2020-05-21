//
// Created by Igli milaqi on 17/05/2020.
//

#include "UnitAnimationSystem.h"
#include "../../Engine/Feather/World.h"
#include "../../Engine/Components/Transform.h"
#include "../Components/UnitAnimationComponent.h"
#include "GLFW/glfw3.h"
void UnitAnimationSystem::Init()
{
    System::Init();
}

void UnitAnimationSystem::Update(float dt)
{
    System::Update(dt);

    auto units = world->EntitiesWith<Transform,UnitAnimationComponent>();

    for (int unitIndex = 0; unitIndex < units.size(); ++unitIndex)
    {
        Transform& unitTransform = world->GetComponent<Transform>(units[unitIndex]);
        UnitAnimationComponent& animationComponent = world->GetComponent<UnitAnimationComponent>(units[unitIndex]);

        glm::vec3 pos = unitTransform.LocalPosition();
        unitTransform.SetLocalPosition(glm::vec3(pos.x,glm::sin(glfwGetTime() * animationComponent.maxSpeed) * animationComponent.height + pos.y,pos.z));
    }
}
