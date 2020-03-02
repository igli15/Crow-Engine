
#include "Debug/Debug.h"

#include "Tests/FeatherTest.h"
#include "Tests/OOPEngineTest.h"

#include "Rendering/Window.h"

int main()
{
    Debug::Log("Init Crow");

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
    return 0;
}

