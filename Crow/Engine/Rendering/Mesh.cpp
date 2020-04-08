//
// Created by Igli milaqi on 08/03/2020.
//

#include "Mesh.h"
#include "../Debug/Debug.h"

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices)
{
    m_vertices = vertices;
    m_indices = indices;

    BufferMesh();
}

void Mesh::Draw(const Shader &shader)
{
    glBindVertexArray(VAO);

    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

void Mesh::BufferMesh()
{
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);
    glGenBuffers(1,&IVBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,m_vertices.size() * sizeof(Vertex),&m_vertices[0],GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uvs));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,m_indices.size() * sizeof(unsigned int),&m_indices[0],GL_STATIC_DRAW);

    glBindVertexArray(0);
}

