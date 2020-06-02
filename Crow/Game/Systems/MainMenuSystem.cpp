//
// Created by Igli milaqi on 02/06/2020.
//

#include "MainMenuSystem.h"
#include "../../Engine/Feather/World.h"
#include "../../Engine/Core/Input.h"
#include "../Components/MainMenuComponent.h"
#include "../../Engine/Core/Game.h"
#include "../Worlds/MainWorld.h"
#include "glm/glm.hpp"
void MainMenuSystem::Init()
{
    System::Init();

    mainWorld = static_cast<MainWorld*>(world);
    m_shouldPlay = false;

    Game::Instance()->fogData.fogDensity = 0.07;
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
            m_shouldPlay = true;
        }
        else if(buttonCounter == 1)
        {
            APP_LOG("Quit");
            Game::Instance()->Close();
        }
    }

    world->ForEach<MainMenuComponent>([&](Entity e,MainMenuComponent& menuComponent)
    {
        if(m_shouldPlay)
        {
            for (int i = 0; i < menuComponent.systemsToEnable.size(); ++i)
            {
                menuComponent.systemsToEnable[i]->enabled = true;
            }

            menuComponent.playButtonHandle.Destroy();
            menuComponent.quitButtonHandle.Destroy();
            world->DestroyEntity(e);
            mainWorld->CreateUIEntities();
            ENGINE_LOG("here");
        }
    });

    if(m_shouldPlay)
    {
        Game::Instance()->fogData.fogDensity = glm::mix(Game::Instance()->fogData.fogDensity, 0.03f, dt);
    }
}
