
#include "Engine/Debug/Debug.h"




#include "Engine/Rendering/Window.h"

#include <iostream>
#include <time.h>
#include "Engine/Core/Game.h"
#include "Engine/Debug/Debug.h"
#include "SandBox/MyGame.h"


int main()
{
    //Debug::Log("Init Crow");

    Debug::Init();
/*
    OOPEngineTest oopTest;
    FeatherTest featherTest;

    oopTest.Init();
    auto t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i <1000 ; ++i)
    {
        oopTest.Update();
    }
    auto t2 = std::chrono::high_resolution_clock::now();

    auto d1 = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

    featherTest.Init();

    auto t3 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i <1000 ; ++i)
    {
        featherTest.Update();
    }
    auto t4 = std::chrono::high_resolution_clock::now();

    auto d2 = std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3).count();

    std::cout<<d1<<";"<<d2<<std::endl;
*/


    MyGame game;
    game.Init();
    game.InitWorld();
    game.Run();

    return 0;
}

