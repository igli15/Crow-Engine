//
// Created by Igli milaqi on 06/03/2020.
//

#include <iostream>
#include "TestSystem.h"

void TestSystem::Init()
{
    System::Init();

    std::cout<<"Initialising System"<<std::endl;
}

void TestSystem::Update()
{
    System::Update();

    for (auto const& entity : m_entities)
    {
        std::cout << "Updating System For entity : " << entity << std::endl;
    }

}
