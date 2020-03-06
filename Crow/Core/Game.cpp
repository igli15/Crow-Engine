//
// Created by Igli milaqi on 05/03/2020.
//

#include "Game.h"
#include "../SandBox/MainWorld.h"

void Game::Init()
{
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
        clock_t  current = clock();
        double elapsed = (double)(current - previous)/CLOCKS_PER_SEC;
        previous = current;
        lag += elapsed;

        while (lag >= MS_PER_UPDATE)
        {
            currentWorld->UpdateAllSystems();
            lag -= MS_PER_UPDATE;
        }

        window->ProcessInput();

        window->ClearColor(0.2,0.3,0.3,1);

        window->SwapBuffers();
        window->PollEvents();
    }

    window->Terminate();
}

void Game::SetWorld(World *w)
{
    currentWorld = w;
}
