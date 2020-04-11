//
// Created by Igli milaqi on 05/04/2020.
//

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Sprite.h"
#include "Shader.h"

void Sprite::Render(int amount)
{
    glActiveTexture(GL_TEXTURE0);
    texture->Bind();

    glBindVertexArray(this->VAO);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6,amount);
    glBindVertexArray(0);
}

void Sprite::Buffer()
{
    GLfloat vertices[] = {
            // Pos      // Tex
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,

            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &m_quadVBO);
    glGenBuffers(1,&m_modelsVBO);

    glBindBuffer(GL_ARRAY_BUFFER, m_quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid *) 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER,m_modelsVBO);
    glBufferData(GL_ARRAY_BUFFER,100000 * sizeof(glm::mat4), nullptr,GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *) 0);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *) (sizeof(glm::vec4)));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *) (2 * sizeof(glm::vec4)));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *) (3 * sizeof(glm::vec4)));

    glVertexAttribDivisor(1, 1);
    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);

    glBindVertexArray(0);
}

void Sprite::BufferModelMatrices(std::vector<glm::mat4> &modelMatrices)
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,(m_modelsVBO));
    glBufferSubData(GL_ARRAY_BUFFER,0,modelMatrices.size() * sizeof(glm::mat4), modelMatrices.data());
    glBindVertexArray(0);
}

Sprite::Sprite()
{
    Buffer();
}

