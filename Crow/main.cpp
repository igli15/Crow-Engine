
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

    MyGame game;
    game.Init();
    game.LoadAssets();
    game.InitWorld();
    game.Run();

    return 0;
}

