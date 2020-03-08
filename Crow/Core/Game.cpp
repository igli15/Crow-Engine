//
// Created by Igli milaqi on 05/03/2020.
//

#include "Game.h"
#include "../SandBox/MainWorld.h"
#include "../Rendering/Shader.h"

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

    Shader shader("../Assets/VertexShader.vs","../Assets/FragmentShader.fs");

    float vertices[] = {
            // positions         // colors
            0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
            0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    while(window->isOpen())
    {
        window->ClearColor(0.2,0.3,0.3,1);

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
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

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
