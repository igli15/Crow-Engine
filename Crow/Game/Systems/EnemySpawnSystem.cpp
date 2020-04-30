//
// Created by Igli milaqi on 30/04/2020.
//

#include "EnemySpawnSystem.h"
#include "../../Engine/Debug/Debug.h"
#include "../Worlds/MainWorld.h"
#include "../UnitGroupArchetypes/AbstractGroupArchetype.h"
#include "../../Engine/Utils/Random.h"

void EnemySpawnSystem::Init()
{
    System::Init();
}

void EnemySpawnSystem::Update(float dt)
{
    System::Update(dt);

    counter += dt;

    MainWorld* mainWorld = static_cast<MainWorld*>(world);


    if(counter > 1)
    {
        //mainWorld->GetUnitGroupArchetype("cubes")->Build();
        counter = 0;
    }
}
