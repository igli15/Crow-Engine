//
// Created by Igli milaqi on 17/03/2020.
//

#include "MyGame.h"
#include "Worlds/RotatingGunsWorld.h"
#include "Worlds/LightingTestWorld.h"

void MyGame::Init()
{
    Game::Init();

    //Set the world here!

    SetWorld(new LightingTestWorld());
    //SetWorld(new RotatingGunsWorld());
}
