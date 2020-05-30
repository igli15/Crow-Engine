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

#include "../../Crow.h"
#include "../Components/Camera.h"
#include "../Components/Light.h"
#include "../Components/Rigidbody.h"
#include "../Components/SphereCollider.h"
#include "../Components/SpriteInfo.h"
#include "../Components/Text.h"
#include "../Components/Transform.h"

Game* Game::m_instance;

void Game::Init()
{
    m_instance = this;

    renderer = new Renderer();
    resourceManager = new ResourceManager();

    window = new Window();
    window->CreateWindow(screenData.screenWidth, screenData.screenHeight, "Crow");

    m_postProcessingShader = resourceManager->CreateShader("PostProcessingShader.vs","PostProcessingShader.fs","postProcessingShader");

    m_postProcessingShader->Use();
    m_postProcessingShader->SetInt("screenTexture", 0);
    window->SetUpPostProcessingFrameBuffer(m_postProcessingShader);

    InitFreeTypeLibrary();

    Random::GenerateSeed();

    m_systemRegistry = new SystemRegistry();
    m_entityRegistry = new EntityRegistry();
    m_componentRegistry = new ComponentRegistry();
    m_poolRegistry = new PoolRegistry();

    AllocateMemory(m_componentRegistry,m_poolRegistry);
}

void Game::InitWorld()
{
    currentWorld->Init(m_systemRegistry,m_entityRegistry,m_componentRegistry,m_poolRegistry);
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
        //window->ClearColor(0.17,0.17,0.17,1);
        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        double  current = glfwGetTime();
        double elapsed = (double)(current - previous);

        if(elapsed > 0.25) elapsed = 0.25;

        previous = current;
        lag += elapsed;

        currentWorld->ClearEntityGarbage();

        window->ProcessInput();

        while (lag >= MS_PER_UPDATE)
        {
            currentWorld->UpdateAllSystems(MS_PER_UPDATE);
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
        if ( currentTime - lastTime >= 0.1 ){ // If last printf() was more than 0.1 sec ago

            timeData.FPS = nbFrames;
            timeData.msPerFrame =  1000.0/double(nbFrames);
            // printf and reset timer
            //printf("%f ms/frame\n", 1000.0/double(nbFrames));
            //printf("%f FPS\n", double(nbFrames));
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

void Game::AllocateMemory(ComponentRegistry* componentRegistry,PoolRegistry* poolRegistry)
{
    componentRegistry->AllocateComponentSet<Camera>();
    componentRegistry->AllocateComponentSet<Light>();
    componentRegistry->AllocateComponentSet<MeshInfo>();
    componentRegistry->AllocateComponentSet<Rigidbody>();
    componentRegistry->AllocateComponentSet<SphereCollider>();
    componentRegistry->AllocateComponentSet<SpriteInfo>();
    componentRegistry->AllocateComponentSet<Text>();
    componentRegistry->AllocateComponentSet<Transform>();
}

