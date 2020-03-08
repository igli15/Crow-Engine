
#include "Debug/Debug.h"

#include "Tests/FeatherTest.h"
#include "Tests/OOPEngineTest.h"

#include "Rendering/Window.h"

#include <iostream>
#include <time.h>
#include "Core/Game.h"
#include "Debug/Debug.h"

int main()
{
    //Debug::Log("Init Crow");

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

    Debug::Init();
    
    Game game;
    game.Init();
    game.Run();

    return 0;
}

