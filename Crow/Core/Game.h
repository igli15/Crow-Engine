//
// Created by Igli milaqi on 05/03/2020.
//

#ifndef CROW_GAME_H
#define CROW_GAME_H


#include "../Rendering/Window.h"
#include "../Feather/World.h"

class Game {

private:
    Window* window;
    World* currentWorld;

public:
    void Init();
    void Run();

    void SetWorld(World* w);


};


#endif //CROW_GAME_H
