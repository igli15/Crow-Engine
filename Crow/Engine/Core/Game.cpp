//
// Created by Igli milaqi on 05/03/2020.
//

#include "Game.h"

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

}

void Game::InitWorld()
{
    currentWorld->Init();
    currentWorld->Build();
    currentWorld->InitAllSystems();
}


void Game::Run()
{
    double previous = glfwGetTime();

    double lag = 0.0;
    double MS_PER_UPDATE = 1.0/60.0;

    double lastTime = glfwGetTime();
    int nbFrames = 0;

    while(window->isOpen())
    {
        window->ClearColor(0.6,0.6,0.6,1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        double  current = glfwGetTime();
        double elapsed = (double)(current - previous);

        previous = current;
        lag += elapsed;

        currentWorld->ClearEntityGarbage();

        while (lag >= MS_PER_UPDATE)
        {
            currentWorld->UpdateAllSystems();
            lag -= MS_PER_UPDATE;
        }

        currentWorld->RenderAllSystems();

        window->ProcessInput();


        window->SwapBuffers();
        window->PollEvents();


        double currentTime = glfwGetTime();
        nbFrames++;
        if ( currentTime - lastTime >= 1.0 ){ // If last prinf() was more than 1 sec ago
            // printf and reset timer
            printf("%f ms/frame\n", 1000.0/double(nbFrames));
            printf("%f FPS\n", double(nbFrames));
            nbFrames = 0;
            lastTime += 1.0;
        }

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

void Game::LoadAssets()
{

}

