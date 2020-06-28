//
// Created by Igli milaqi on 22/05/2020.
//

#ifndef CROW_UNITICONCOMPONENT_H
#define CROW_UNITICONCOMPONENT_H


#include "../../Engine/Rendering/Sprite.h"

struct UnitIconComponent
{
    float unitPrice = 0.0f;
    Sprite* avaiableSprite = nullptr;
    Sprite* unavaibleSprite = nullptr;
};


#endif //CROW_UNITICONCOMPONENT_H
