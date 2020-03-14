//
// Created by Igli milaqi on 05/03/2020.
//

#include "Game.h"
#include "../../SandBox/MainWorld.h"
#include "../Rendering/Shader.h"
#include "../Rendering/Model.h"
#include "ResourceManager.h"

#include "glm/ext.hpp"

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

    Shader shader("VertexShader.vs","FragmentShader.fs");

    Model crysisModel((MODEL_PATH + "nanosuit.obj").data());

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
            //currentWorld->UpdateAllSystems();
            lag -= MS_PER_UPDATE;
        }


        shader.Use();

        glm::mat4 projection = glm::perspective(glm::radians(45.0f),1920.0f/1080.0f, 0.1f, 100.0f);
        glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
        glm::mat4 view = glm::lookAt(cameraPos,glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f));
        shader.SetMat4("projection", projection);
        shader.SetMat4("view", view);

        //std::cout<<crysisModel.m_meshes[0].m_vertices[10].pos.x <<std::endl;
        //std::cout<<crysisModel.m_meshes[0].m_indices.size()<<std::endl;
        //std::cout<<crysisModel.m_meshes[0].VBO<<std::endl;

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.2, 0.2, 0.2));
        shader.SetMat4("model", model);
        crysisModel.Draw(shader);


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
