//
// Created by Igli milaqi on 05/03/2020.
//

#ifndef CROW_GAME_H
#define CROW_GAME_H


#include "../Rendering/Window.h"
#include "../Feather/World.h"

#include "freetype2/ft2build.h"
#include FT_FREETYPE_H

class ResourceManager;

class Game {

private:
    Window* window;
    World* currentWorld;

    static Game* m_instance;

    void InitFreeTypeLibrary();
public:
    virtual void Init();
    virtual void LoadAssets();
    void InitWorld();
    void Run();

    void SetWorld(World* w);
    static Game* Instance();

    FT_Library* ftLibrary;
    ResourceManager* resourceManager;

};


#endif //CROW_GAME_H
