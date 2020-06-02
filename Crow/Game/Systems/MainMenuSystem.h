//
// Created by Igli milaqi on 02/06/2020.
//

#ifndef CROW_MAINMENUSYSTEM_H
#define CROW_MAINMENUSYSTEM_H


#include "../../Engine/Feather/System.h"


class MainWorld;

class MainMenuSystem : public System
{
public:

    void Init() override;
    void Update(float dt) override;
    MainWorld* mainWorld;
private:
    int buttonCounter = 0;
    bool m_shouldPlay = false;
};


#endif //CROW_MAINMENUSYSTEM_H
