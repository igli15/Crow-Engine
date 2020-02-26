
#include "Debug/Debug.h"

#include "Tests/FeatherTest.h"
#include "Tests/OOPEngineTest.h"

int main()
{
    Debug::Log("Init Crow");

    FeatherTest test;
    OOPEngineTest OOPEngine;


    test.Init();
    OOPEngine.Init();

    auto t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i <1000; ++i)
    {
        test.Update();
    }
    auto t2 = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
    std::cout<<duration<<std::endl;

    auto t3 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i <1000 ; ++i)
    {
        OOPEngine.Update();
    }
    auto t4 = std::chrono::high_resolution_clock::now();

    auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>( t4 - t3 ).count();
    std::cout<<duration2<<std::endl;

    Debug::Log("Closing Crow");


    return 0;
}
