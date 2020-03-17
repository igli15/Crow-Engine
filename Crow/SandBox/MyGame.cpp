//
// Created by Igli milaqi on 17/03/2020.
//

#include "MyGame.h"
#include "Worlds/RotatingGunsWorld.h"

void MyGame::Init()
{
    Game::Init();

    //Set the world here!

    SetWorld(new RotatingGunsWorld());
}
