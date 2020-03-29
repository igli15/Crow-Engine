//
// Created by Igli milaqi on 05/03/2020.
//

#ifndef CROW_GAME_H
#define CROW_GAME_H


#include "../Rendering/Window.h"
#include "../Feather/World.h"

class ResourceManager;

class Game {

private:
    Window* window;
    World* currentWorld;

    static Game* m_instance;

public:
    virtual void Init();
    virtual void LoadAssets();
    void InitWorld();
    void Run();

    void SetWorld(World* w);
    static Game* Instance();

    ResourceManager* resourceManager;

};


#endif //CROW_GAME_H
