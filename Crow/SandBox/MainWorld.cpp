//
// Created by Igli milaqi on 06/03/2020.
//

#include "MainWorld.h"
#include "../Tests/FeatherTest.h"
#include "Systems/TestSystem.h"

struct TestComponent{

};

void MainWorld::Build()
{
    RegisterSystem<TestSystem>();
    SetSystemSignature<TestSystem,TestComponent>();

    EntityHandle entity  = CreateEntity();
    entity.AddComponent(TestComponent{});
    entity.RemoveComponent<TestComponent>();
}
