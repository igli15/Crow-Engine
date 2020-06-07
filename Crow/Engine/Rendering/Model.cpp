//
// Created by Igli milaqi on 09/03/2020.
//

#include "Model.h"
#include "../../Crow.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

void Model::Draw() {
    //std::cout<<"Meshes: "<< m_meshes.size()<<std::endl;

    for (int i = 0; i < m_meshes.size(); ++i)
    {
       // m_meshes[i].Draw();
    }
}

void Model::LoadModel(const std::string &path) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path.data(), aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        ENGINE_LOG_ERROR("Mesh was not loaded correctly. Path: " + path);
        return;
    }

    directory = path.substr(0, path.find_last_of('/'));

    ProcessNode(scene->mRootNode, scene);

}

void Model::ProcessNode(aiNode *node, const aiScene *scene) {
    for (int i = 0; i < node->mNumMeshes; ++i) {
        aiMesh *m = scene->mMeshes[node->mMeshes[i]];
        m_meshes.push_back(ProcessMesh(m, scene));
    }

    //recursively process all the child nodes as well
    for (int j = 0; j < node->mNumChildren; ++j) {
        ProcessNode(node->mChildren[j], scene);
    }
}

Mesh Model::ProcessMesh(aiMesh *mesh, const aiScene *scene) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        glm::vec3 vector;
        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.pos = vector;
        // normals
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.normal = vector;
        // texture coordinates

        if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.uvs = vec;
        } else
            vertex.uvs = glm::vec2(0.0f, 0.0f);

        /*
        vector.x = mesh->mTangents[i].x;
        vector.y = mesh->mTangents[i].y;
        vector.z = mesh->mTangents[i].z;
        vertex.tangent = vector;


        vector.x = mesh->mBitangents[i].x;
        vector.y = mesh->mBitangents[i].y;
        vector.z = mesh->mBitangents[i].z;
        vertex.biTangent = vector;
*/

        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    return Mesh(vertices, indices);
}

void Model::InstanceBufferMeshes()
{
    for (int meshIndex = 0; meshIndex < m_meshes.size(); ++meshIndex)
    {
        unsigned int VAO = m_meshes[meshIndex].VAO;
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER,m_meshes[meshIndex].IVBO);

        glBufferData(GL_ARRAY_BUFFER,maxNumberOfModelInstances * sizeof(glm::mat4), nullptr,GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *) 0);
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *) (sizeof(glm::vec4)));
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *) (2 * sizeof(glm::vec4)));
        glEnableVertexAttribArray(6);
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *) (3 * sizeof(glm::vec4)));

         glVertexAttribDivisor(3, 1);
        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);
        glVertexAttribDivisor(6, 1);
    }

}

void Model::InstanceRenderMeshes(int amount)
{
    for (unsigned int meshIndex = 0; meshIndex < m_meshes.size(); meshIndex++)
    {
        glBindVertexArray(m_meshes[meshIndex].VAO);
        glDrawElementsInstanced(GL_TRIANGLES, m_meshes[meshIndex].m_indices.size(), GL_UNSIGNED_INT, 0, amount);
        glBindVertexArray(0);
    }
}

void Model::BindModelBuffer(const std::vector<glm::mat4>& models)
{
    for (int i = 0; i < m_meshes.size(); ++i)
    {
        glBindVertexArray(m_meshes[i].VAO);
        glBindBuffer(GL_ARRAY_BUFFER,(m_meshes[i].IVBO));
        glBufferSubData(GL_ARRAY_BUFFER,0,models.size() * sizeof(glm::mat4), models.data());
        glBindVertexArray(0);
    }

}
