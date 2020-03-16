//
// Created by Igli milaqi on 05/03/2020.
//

#include "Game.h"

#include "../../SandBox/MainWorld.h"
#include "../Rendering/Shader.h"
#include "../Rendering/Model.h"
#include "glm/ext.hpp"
#include "ResourceManager.h"


Game* Game::m_instance;

void Game::Init()
{
    m_instance = this;

    resourceManager = new ResourceManager();

    window = new Window();

    window->CreateWindow(1920,1080,"Crow");

    currentWorld = new MainWorld();
    currentWorld->Init();
    currentWorld->Build();
    currentWorld->InitAllSystems();
}

void Game::Run()
{
    clock_t previous = clock();
    double lag = 0.0;
    double MS_PER_UPDATE = 1.0/60.0;


    while(window->isOpen())
    {
        window->ClearColor(0.1,0,0,1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        clock_t  current = clock();
        double elapsed = (double)(current - previous)/CLOCKS_PER_SEC;
        previous = current;
        lag += elapsed;

        while (lag >= MS_PER_UPDATE)
        {
            currentWorld->UpdateAllSystems();
            lag -= MS_PER_UPDATE;
        }

        currentWorld->RenderAllSystems();

        window->ProcessInput();


        window->SwapBuffers();
        window->PollEvents();
    }


    window->Terminate();
}

void Game::SetWorld(World *w)
{
    currentWorld = w;
}

Game *Game::Instance()
{
    return m_instance;
}