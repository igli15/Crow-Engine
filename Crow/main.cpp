
#include "Debug/Debug.h"

#include "Tests/FeatherTest.h"
#include "Tests/OOPEngineTest.h"

#include "Rendering/Window.h"

#include <iostream>

int main()
{
    //Debug::Log("Init Crow");


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

    //std::cout<<d1 <<std::endl;

    featherTest.Init();

    auto t3 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i <1000 ; ++i)
    {
        featherTest.Update();
    }
    auto t4 = std::chrono::high_resolution_clock::now();

    auto d2 = std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3).count();

    //std::cout<<d2 <<std::endl;

    std::cout<<d1<<";"<<d2<<std::endl;

    /*
    Window window;

    window.CreateWindow(1920,1080,"Crow");

    while (window.isOpen())
    {
        window.ProcessInput();

        window.ClearColor(0.2,0.3,0.3,1);

        window.SwapBuffers();
        window.PollEvents();
    }

    window.Terminate();
    */


    return 0;
}

