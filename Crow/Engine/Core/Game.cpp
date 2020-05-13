//
// Created by Igli milaqi on 05/03/2020.
//

#include "Game.h"

#include "../Rendering/Shader.h"
#include "../Rendering/Model.h"
#include "glm/ext.hpp"
#include "ResourceManager.h"
#include "Input.h"
#include "Renderer.h"
#include "../Utils/Random.h"

#include "AssetParser.h"
#include "../../Crow.h"

Game* Game::m_instance;

void Game::Init()
{
    m_instance = this;

    renderer = new Renderer();
    resourceManager = new ResourceManager();

    window = new Window();
    window->CreateWindow(1920, 1080, "Crow");


    //TODO: doing post processing stuff here move to window class later

    m_postProcessingShader = resourceManager->CreateShader("PostProcessingShader.vs","PostProcessingShader.fs","postProcessingShader");

    m_postProcessingShader->Use();
    m_postProcessingShader->SetInt("screenTexture", 0);
    window->SetUpPostProcessingFrameBuffer(m_postProcessingShader);

    InitFreeTypeLibrary();

    Random::GenerateSeed();
}

void Game::InitWorld()
{
    currentWorld->Init();
    currentWorld->Build();
    currentWorld->InitAllSystems();

    ParseFile((ASSET_PATH + "allAssets.asset").data());
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
        //window->ClearColor(0.17,0.17,0.17,1);
        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        double  current = glfwGetTime();
        double elapsed = (double)(current - previous);

        previous = current;
        lag += elapsed;

        currentWorld->ClearEntityGarbage();

        window->ProcessInput();

        while (lag >= MS_PER_UPDATE)
        {
            currentWorld->UpdateAllSystems(elapsed);
            lag -= MS_PER_UPDATE;
        }


        glBindFramebuffer(GL_FRAMEBUFFER, window->internalFrameBuffer);
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        currentWorld->PreRenderAllSystems();
        currentWorld->RenderAllSystems();

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDisable(GL_DEPTH_TEST);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        m_postProcessingShader->Use();
        glBindVertexArray(window->quadVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, window->internalTextureColorBuffer);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        window->SwapBuffers();
        window->PollEvents();


        double currentTime = glfwGetTime();
        nbFrames++;
        if ( currentTime - lastTime >= 1.0 ){ // If last printf() was more than 1 sec ago
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
    resourceManager->CreateShader("TextVertexShader.vs","TextFragmentShader.fs","textShader");
    resourceManager->LoadFont(("Roboto-Light.ttf"),"roboto");
    resourceManager->LoadTexture("whiteTexture.png","whiteTexture");
    resourceManager->LoadTexture("blackTexture.png","blackTexture");
}

void Game::InitFreeTypeLibrary()
{
    ftLibrary = new FT_Library();

    if (FT_Init_FreeType(ftLibrary))
    {
       ENGINE_LOG_CRITICAL("FreeType wasn't initialized correctly!");
    }
}

