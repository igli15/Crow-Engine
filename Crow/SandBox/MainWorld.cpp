//
// Created by Igli milaqi on 06/03/2020.
//

#include "MainWorld.h"
#include "../Tests/FeatherTest.h"
#include "Systems/TestSystem.h"

#include "../Engine/Components/Transform.h"


void MainWorld::Build()
{
    RegisterSystem<TestSystem>();
    SetSystemSignature<TestSystem,Transform>();

    EntityHandle entity  = CreateEntity();
    entity.AddComponent(Transform{glm::vec3(0,0,0),glm::vec3(0,0,0),glm::quat()});
}
