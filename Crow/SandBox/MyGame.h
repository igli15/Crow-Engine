//
// Created by Igli milaqi on 17/03/2020.
//

#ifndef CROW_MYGAME_H
#define CROW_MYGAME_H


#include "../Engine/Core/Game.h"
#include "../Plugins/RapidXML/rapidxml.hpp"

class MyGame : public Game {

public:
    void Init() override;
    void LoadAssets() override;
    void AllocateMemory() override;

};


#endif //CROW_MYGAME_H
