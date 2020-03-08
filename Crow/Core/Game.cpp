//
// Created by Igli milaqi on 05/03/2020.
//

#include "Game.h"
#include "../SandBox/MainWorld.h"
#include "../Rendering/Shader.h"
#include "ResourceLoader.h"

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

    float vertices[] = {
            // positions          // colors           // texture coords
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
    };


    unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };

    unsigned int VBO, VAO,EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned int texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    ResourceLoader resourceLoader;

    Texture& tex = resourceLoader.LoadTexture("container.jpg","container");


    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex.width, tex.height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex.data);
    glGenerateMipmap(GL_TEXTURE_2D);

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

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        shader.Use();

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        window->ProcessInput();


        window->SwapBuffers();
        window->PollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    window->Terminate();
}

void Game::SetWorld(World *w)
{
    currentWorld = w;
}
