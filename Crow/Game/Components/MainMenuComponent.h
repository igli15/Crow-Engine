//
// Created by Igli milaqi on 02/06/2020.
//

#ifndef CROW_MAINMENUCOMPONENT_H
#define CROW_MAINMENUCOMPONENT_H


#include "../../Engine/Feather/EntityHandle.h"

class System;
struct MainMenuComponent
{
    std::vector<System*> systemsToEnable{};
    EntityHandle playButtonHandle;
    EntityHandle quitButtonHandle;
    EntityHandle selectionIconHandle;
    int playButtonYPos = 0;
    int quitButtonYPos = 0;
};


#endif //CROW_MAINMENUCOMPONENT_H
