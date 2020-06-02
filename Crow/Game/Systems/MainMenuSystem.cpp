//
// Created by Igli milaqi on 02/06/2020.
//

#include "MainMenuSystem.h"
#include "../../Engine/Feather/World.h"
#include "../../Engine/Core/Input.h"

void MainMenuSystem::Init()
{
    System::Init();
}

void MainMenuSystem::Update(float dt)
{
    if(Input::GetKeyDown(GLFW_KEY_DOWN))
    {
        buttonCounter++;
        if(buttonCounter > 1)
            buttonCounter = 0;
    }
    else if(Input::GetKeyDown(GLFW_KEY_UP))
    {
        buttonCounter--;
        if(buttonCounter < 0)
            buttonCounter = 0;
    }

    if(Input::GetKeyDown(GLFW_KEY_ENTER))
    {
        if(buttonCounter == 0)
        {
            APP_LOG("Play");
        }
        else if(buttonCounter == 1)
        {
            APP_LOG("Quit");
        }
    }
}
