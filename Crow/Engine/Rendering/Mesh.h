//
// Created by Igli milaqi on 08/03/2020.
//

#ifndef CROW_MESH_H
#define CROW_MESH_H


#include "glm/glm.hpp"
#include "Shader.h"
#include <vector>

struct Vertex
{
public:
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec3 tangent;
    glm::vec3 biTangent;
    glm::vec2 uvs;
};

struct Mesh {

//private:
public:
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;

public:
    Mesh(const std::vector<Vertex>& vertices,const std::vector<unsigned int>& m_indices);
    void Draw();

    //TODO if one of these vbo is not copied things break!!!
    Mesh(const Mesh &otherMesh) : m_vertices(otherMesh.m_vertices), m_indices(otherMesh.m_indices) , VAO(otherMesh.VAO),
                                  VBO(otherMesh.VBO), EBO(otherMesh.EBO),IVBO(otherMesh.IVBO)
    {
        //std::cout<<"Copying"<<std::endl;
        //BufferMesh();
    }

//private:
    unsigned int VAO,VBO,EBO,IVBO;
    void BufferMesh();
};


#endif //CROW_MESH_H
