//
// Created by Igli milaqi on 05/03/2020.
//

#ifndef CROW_GAME_H
#define CROW_GAME_H


#include "../Rendering/Window.h"
#include "../Feather/World.h"

#include "freetype2/ft2build.h"
#include FT_FREETYPE_H

class Renderer;
class ResourceManager;

///The game class handles all the internal setup for a "game" program to run.
///It's the parent class of "MyGame" which is what the user should use and create.
class Game {

private:
    Window* window;
    World* currentWorld;

    static Game* m_instance;

    ///Initializes the FreeType Library used to load fonts
    void InitFreeTypeLibrary();
public:
    virtual void Init();

    ///Here is where all the assets should be loaded
    virtual void LoadAssets();

    ///Initializes the current world
    void InitWorld();

    ///Runs the Game loop
    void Run();

    ///Sets the current world
    ///@param w The new world which will be updated
    void SetWorld(World* w);

    ///Returns the singelton instance of "Game" class.
    ///@return A pointer to the Game class instance
    static Game* Instance();

    FT_Library* ftLibrary;
    ResourceManager* resourceManager;
    Renderer* renderer;

};


#endif //CROW_GAME_H
